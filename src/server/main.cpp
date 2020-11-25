#include <restbed>
#include <nlohmann/json.hpp>
#include <cstring>
#include <cstdlib>
#include <memory>
#include <string>
#include <fstream>
#include <iostream>
#include <utility>
#include <map>
#include "../../include/service/Comment.h"
#include "../../include/service/Issue.h"
#include "../../include/service/User.h"

using json = nlohmann::json;

// Response header to prevent a cross-site validation problem
#define ALLOW_ALL { "Access-Control-Allow-Origin", "*" }

// Response header to close connection
#define CLOSE_CONNECTION { "Connection", "close" }

struct issue {
    std::string name;
    std::string issueMessage;
};

std::map<int, User*> users;
std::map<int, Issue*> issues;
int userIDX, issueIDX;

void parse(const char* data, User*& user) {
    char* data_mutable = const_cast<char*>(data);
    char* name          = strtok_r(data_mutable, "\n", &data_mutable);
    char* group         = strtok_r(nullptr, "\n", &data_mutable);
    unsigned int id     = users.size();

    user = new User(id, name);
    user->setGroup( std::stoul(group) );
}


void post_request(const std::shared_ptr<restbed::Session >&
                  session, const restbed::Bytes & body) {
    User* u;
    const char* data = reinterpret_cast<const char*>(body.data());
    parse(data, u);

    nlohmann::json resultJSON;
    resultJSON["id"]    = u->getID();
    resultJSON["name"]  = u->getName();
    resultJSON["group"] = u->group;
    // resultJSON["id"]    = 0;
    // resultJSON["name"]  = "Don";
    // resultJSON["group"] = 0;
    std::string response = resultJSON.dump();

    session->close(restbed::OK, response, { ALLOW_ALL, { "Content-Length", std::to_string(response.length()) }, CLOSE_CONNECTION });
}


void post_issue_handler(const std::shared_ptr<restbed::Session>& session) {
    const auto request      = session->get_request();
    size_t content_length   = request->get_header("Content-Length", 0);

    session->fetch(content_length, &post_request);
}

void get_issue_handler(const std::shared_ptr<restbed::Session>& session) {
    const auto request = session->get_request();

    // if (request->has_query_parameter("name")) {
    //     exp.name = request->get_query_parameter("name");
    //     if (request->has_query_parameter("issueMessage")) {
    //         exp.issueMessage = request->get_query_parameter("issueMessage");
    //     }
    // }

    json j;
    std::fstream f("./db.json");
    j = json::parse(f);

    json resultJSON;
    resultJSON["users"] = j["users"];

    std::string response = resultJSON.dump(4);

    session->close(restbed::OK, response, { ALLOW_ALL, { "Content-Length", std::to_string(response.length()) }, CLOSE_CONNECTION });
}



void readDB() {
    json j;
    std::fstream f("./db.json");
    j = json::parse(f);

    userIDX = j["userIDX"];
    issueIDX = j["issueIDX"];

    // create user objects
    for (auto &u : j["users"]) {
        User* user = new User(u["id"], u["name"]);
        user->setGroup(u["group"]);
        users.insert(std::make_pair(u["id"], user));
    }

    // create issue objects
    for (auto &i : j["issues"]) {
        Issue* issue = new Issue(i["id"], i["title"], users[i["author"]]);
        issue->setType(i["type"]);
        issue->setStatus(i["status"]);
        issue->setDescription(i["description"]);
        //issue->setCommentIDX(i["commentIDX"]);

        for (auto &a : i["assignees"])
            issue->addAssignee(users[a]);

        for (auto &c : i["comments"])
            issue->addComment(new Comment(c["id"], users[c["author"]], c["comment"]));

        issues.insert(std::make_pair(i["id"], issue));
    }
}


int main(const int, const char**) {
    readDB();

    // TESTING READ
    // std::cout << "\n";
    // for (auto i : users) {
    //     User* u = i.second;
    //     std::cout << *u;
    // }

    // for (auto i : issues) {
    //     Issue* s = i.second;
    //     std::cout << *s;
    // }

    // Setup service and request handlers
    auto resource = std::make_shared<restbed::Resource>();
    resource->set_path("/users");
    resource->set_method_handler("POST", post_issue_handler);
    resource->set_method_handler("GET", get_issue_handler);

    auto settings = std::make_shared<restbed::Settings>();
    settings->set_port(1234);

    // Publish and start service
    restbed::Service service;
    service.publish(resource);

    service.start(settings);
    return EXIT_SUCCESS;
}
