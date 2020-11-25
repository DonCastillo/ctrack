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
    std::string response = resultJSON.dump();
    // @todo store new user to the map or file?

    session->close(restbed::OK, response, { ALLOW_ALL, { "Content-Length", std::to_string(response.length()) }, CLOSE_CONNECTION });
}


void post_issue_handler(const std::shared_ptr<restbed::Session>& session) {
    const auto request      = session->get_request();
    size_t content_length   = request->get_header("Content-Length", 0);

    session->fetch(content_length, &post_request);
}



void get_issue_handler(const std::shared_ptr<restbed::Session>& session) {
    const auto request = session->get_request();
    std::fstream f("./db.json");
    json j = json::parse(f);
    json resultJSON;

    /**
        GET     /users              lists all users
        POST    /users              creates a new user
        GET     /users/{id}         views user info based on id
        PUT     /users/{id}         updates user info based on id
        DELETE  /users/{id}         deletes user info based on id
        GET     /users?group=val    lists all users in a particular group
    */


    if ( request->has_path_parameter("id") ) {
        std::string targetID = request->get_path_parameter("id");

        // search user based on id
        for (auto &u : j["users"]) {
            if( u["id"] == std::stoi(targetID) ) {
                resultJSON = u;
                break;
            }
        }

    } else {

        if ( request->has_query_parameter("group") ) {
            // search for all users that belong in a specified group
            std::string targetGroup = request->get_query_parameter("group"); // developer
            json collection = json::array(); // initialize to empty array
            for (auto &u : j["users"]) {
                std::string userGroup = User::getGroup(u["group"]);
                if( targetGroup == userGroup )
                    collection.push_back(u);
            }
            resultJSON["users"] = collection;
        } else {
            // if no id or query is specified, get all users
            resultJSON["users"] = j["users"];
        }

    }

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

    f.close();
}

void writeDB() {
    json j;
    std::ofstream f("./db.json");

    // Add indexing to JSON object
    j["userIDX"] = userIDX;
    j["issueIDX"] = issueIDX;
    j["users"] = json::array();
    j["issues"] = json::array();

    // Add users to JSON object
    for (auto &u : users) {
        json user;
        user["id"] = u.second->getID();
        user["name"] = u.second->getName();
        user["group"] = u.second->getGroup();
        j["users"].push_back(user);
    }

    // Add Issues to JSON object
    for (auto &i : issues) {
        json issue;
        issue["id"] = i.second->getID();
        issue["title"] = i.second->getTitle();
        issue["description"] = i.second->getDescription();
        issue["author"] = i.second->getIssuer()->getID();
        issue["type"] = i.second->getType();
        issue["status"] = i.second->getStatus();
        issue["assignees"] = json::array();
        issue["comments"] = json::array();

        // Adding assignees to issue
        for (auto a : i.second->getAssignees())
            issue["assignees"].push_back(a->getID());

        // Adding comments to issue
        for (auto c : i.second->getComments()) {
            json comment;
            comment["id"] = c->getID();
            comment["comment"] = c->getComment();
            comment["author"] = c->getCommenter()->getID();
            issue["comments"].push_back(comment);
        }

        j["issues"].push_back(issue);
    }

    // Write to file
    std::cout << "SERVER WRITING DATA" << std::endl;
    f << j;
    f.close();
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
    resource->set_paths( { "/users", "/users/{id: .*}" } );
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
