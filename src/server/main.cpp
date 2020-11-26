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

/** Response header to prevent a cross-site validation problem */
#define ALLOW_ALL { "Access-Control-Allow-Origin", "*" }

/** Response header to close connection */
#define CLOSE_CONNECTION { "Connection", "close" }


/*++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*             Function declaration                   */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void parse_user(const char* data, User*& user);
void post_user_request(const std::shared_ptr<restbed::Session >& session,
                       const restbed::Bytes & body);
void post_user_handler(const std::shared_ptr<restbed::Session>& session);
void get_user_handler(const std::shared_ptr<restbed::Session>& session);
void readDB();
void writeDB();


/*++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*                  Variables                         */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++*/
std::map<int, User*> users;
std::map<int, Issue*> issues;
int userIDX, issueIDX;


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*             Function definitions                    */
/*******************************************************/



/* ++++++++++++++++++++++++++++++++++
    User functions
+++++++++++++++++++++++++++++++++++++ */

/**
 * @brief parses the string data and convert it to actual USER object   
 * @param data  actual data sent from the client
 * @param user  USER object to be filled with data members
 */
void parse_user(const char* data, User*& user) {
    char* data_mutable = const_cast<char*>(data);
    char* name          = strtok_r(data_mutable, "\n", &data_mutable);
    char* group         = strtok_r(nullptr, "\n", &data_mutable);
    
    // new user gets an ID based on value of userID
    unsigned int id     = ++userIDX;  

    user = new User(id, name);
    user->setGroup(std::stoul(group));
}


/**
 * @brief creates a new USER object and inserts it into the users map
 *        closes the session after      
 * @param session   current session between server and client
 * @param body      body of the request
 */
void post_user_request(const std::shared_ptr<restbed::Session >&
                       session, const restbed::Bytes & body) {
    User* u;
    const char* data = reinterpret_cast<const char*>(body.data());
    parse_user(data, u);

    nlohmann::json resultJSON;
    resultJSON["result"]    = "New user is added";

    // info to be sent back to the client
    std::string response = resultJSON.dump();

    // info to be stored in the server
    users.insert(std::make_pair(u->getID(), u));

    // update db
    writeDB();
    session->close(restbed::OK, response, { ALLOW_ALL, { "Content-Length", std::to_string(response.length()) }, CLOSE_CONNECTION });
}



/**
 * @brief handles the POST request for the USER
 * @param session   current session between server and client 
 */
void post_user_handler(const std::shared_ptr<restbed::Session>& session) {
    const auto request      = session->get_request();
    size_t content_length   = request->get_header("Content-Length", 0);
    session->fetch(content_length, &post_user_request);
}



/**
 * @brief handles the DELETE request for the USER
 * @param session   current session between server and client
 */
void delete_user_handler(const std::shared_ptr<restbed::Session>& session) {
    const auto request      = session->get_request();
    std::map<int, User*>::iterator it;
    std::string message;
    json resultJSON;

    if (request->has_path_parameter("id")) {
        std::string paramID = request->get_path_parameter("id");
        int targetID        = std::stoi(paramID);

        it = users.find(targetID);
        if (it != users.end()) {
            users.erase(it);
            message = "User successfully delete";
            writeDB();
        } else {
            message = "User not found";
        }

    } else {
        message = "User not found";
    }

    resultJSON["result"]    = message;
    std::string response    = resultJSON.dump();
    session->close(restbed::OK, response, { ALLOW_ALL, { "Content-Length", std::to_string(response.length()) }, CLOSE_CONNECTION });
}


/**
 * @brief handles the GET request for the USER
 * @param session   current session between server and client
 */
void get_user_handler(const std::shared_ptr<restbed::Session>& session) {
    const auto request = session->get_request();
    std::fstream f("./db.json");
    json j = json::parse(f);
    json resultJSON;

    if (request->has_path_parameter("id")) {
        std::string targetID = request->get_path_parameter("id");

        // search user based on id
        for (auto &u : j["users"]) {
            if (u["id"] == std::stoi(targetID)) {
                resultJSON = u;
                break;
            }
        }
        // if the user based on id is not found
        if (resultJSON.empty())
            resultJSON["result"] = "No user found";

    } else {
        if (request->has_query_parameter("group")) {
            std::string targetGroup = request->get_query_parameter("group");
            json collection         = json::array();

            for (auto &u : j["users"]) {
                std::string userGroup = User::getGroup(u["group"]);
                if (targetGroup == userGroup)
                    collection.push_back(u);
            }
            // get all users in the same group
            resultJSON["users"] = collection;
        } else {
            // if no id or query is specified, get all users
            resultJSON["users"] = j["users"];
        }
    }

    std::string response = resultJSON.dump(4);
    session->close(restbed::OK, response, { ALLOW_ALL, { "Content-Length", std::to_string(response.length()) }, CLOSE_CONNECTION });
}

/* ++++++++++++++++++++++++++++++++++
    End of User functions
+++++++++++++++++++++++++++++++++++++ */





/*!
   \brief   reads the JSON file
   \pre     call this function in the main function to load all the objects
*/
void readDB() {
    json j;
    std::fstream f("./db.json");
    j = json::parse(f);

    userIDX  = j["userIDX"];
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

        for (auto &a : i["assignees"])
            issue->addAssignee(users[a]);

        for (auto &c : i["comments"])
            issue->addComment(new Comment(c["id"], users[c["author"]], c["comment"]));

        issues.insert(std::make_pair(i["id"], issue));
    }

    f.close();
}




/*!
   \brief   updates the JSON file
   \pre     call this function every time a user or issue
            object is added, deleted, or updated
*/
void writeDB() {
    json j;
    std::ofstream f("./db.json");

    // Add indexing to JSON object
    j["userIDX"]  = userIDX;
    j["issueIDX"] = issueIDX;
    j["users"]    = json::array();
    j["issues"]   = json::array();

    // Add users to JSON object
    for (auto &u : users) {
        json user;
        user["id"]    = u.second->getID();
        user["name"]  = u.second->getName();
        user["group"] = u.second->getGroup();
        j["users"].push_back(user);
    }

    // Add Issues to JSON object
    for (auto &i : issues) {
        json issue;
        issue["id"]          = i.second->getID();
        issue["title"]       = i.second->getTitle();
        issue["description"] = i.second->getDescription();
        issue["author"]      = i.second->getIssuer()->getID();
        issue["type"]        = i.second->getType();
        issue["status"]      = i.second->getStatus();
        issue["assignees"]   = json::array();
        issue["comments"]    = json::array();

        // Adding assignees to issue
        for (auto a : i.second->getAssignees())
            issue["assignees"].push_back(a->getID());

        // Adding comments to issue
        for (auto c : i.second->getComments()) {
            json comment;
            comment["id"]       = c->getID();
            comment["comment"]  = c->getComment();
            comment["author"]   = c->getCommenter()->getID();
            issue["comments"].push_back(comment);
        }

        j["issues"].push_back(issue);
    }

    // Write to file
    std::cout << "SERVER UPDATING DATA" << std::endl;
    f << j;
    f.close();
}



/*++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*                    MAIN FUNCTION                     */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

int main(const int, const char**) {
    readDB();

    /**
        GET     /users                      lists all users
        POST    /users                      creates a new user
        GET     /users/{id}                 views user info based on id
        DELETE  /users/{id}                 deletes user info based on id
        GET     /users?group=val            lists all users in a particular group

        GET     /issues                     lists all issues
        POST    /issues                     creates a new issue
        GET     /issues/{id}                views issue based on id
        DELETE  /issues/{id}                deletes issue based on id
        PUT     /issues/{id}                updates issue based on id
        GET     /issues/{id}/comments       lists all comments of an id-specified issue
        POST    /issues/{id}/comments       adds a comment for an issue
        GET     /issues/{id}/comments/{id}  views a specific comment of an issue based on id
        PUT     /issues/{id}/comments/{id}  updates a comment of an id-specified issue
        DELETE  /issues/{id}/comments/{id}  deletes a comment of an id-specified issue
        GET     /issues?type=val
                /issues?status=val
                /issues?start=0&end=0       if start == end, then /issues/{id}
                /issues?start=3&end=0       if start > end, then return result : "No issues found"
                /issues?start=0&end=2       returns issues with id 0 through 2
    */

    // Setup service and request handlers
    auto resource_users = std::make_shared<restbed::Resource>();
    resource_users->set_path("/users");
    resource_users->set_method_handler("POST", post_user_handler);
    resource_users->set_method_handler("GET", get_user_handler);

    auto resource_user_by_id = std::make_shared<restbed::Resource>();
    resource_user_by_id->set_path("/users/{id: .*}");
    resource_user_by_id->set_method_handler("GET", get_user_handler);
    resource_user_by_id->set_method_handler("DELETE", delete_user_handler);



    auto settings = std::make_shared<restbed::Settings>();
    settings->set_port(1234);

    // Publish and start service
    restbed::Service service;
    service.publish(resource_users);
    service.publish(resource_user_by_id);

    service.start(settings);
    return EXIT_SUCCESS;
}
