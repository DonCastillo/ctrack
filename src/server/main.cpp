#include <restbed>
#include <cstring>
#include <cstdlib>
#include <memory>
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <utility>
#include <map>
#include <nlohmann/json.hpp>
#include "../../include/service/Comment.h"
#include "../../include/service/Issue.h"
#include "../../include/service/User.h"

using json = nlohmann::json;

/** Response header to prevent a cross-site validation problem */
#define ALLOW_ALL { "Access-Control-Allow-Origin", "*" }

/** Response header to close connection */
#define CLOSE_CONNECTION { "Connection", "close" }

#define JSON { "Content-Type", "application/json" }



/*++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*             Function declaration                   */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void parse_user(const char* data, User*& user);
void post_user_request(const std::shared_ptr<restbed::Session >& session,
                       const restbed::Bytes & body);
void post_user_handler(const std::shared_ptr<restbed::Session>& session);
void get_user_handler(const std::shared_ptr<restbed::Session>& session);
void post_issue_request(const std::shared_ptr<restbed::Session >&
                       session, const restbed::Bytes & body);
void post_issue_handler(const std::shared_ptr<restbed::Session>& session);
void parse_issue(const char* data, Issue*& issue);
void delete_issue_handler(const std::shared_ptr<restbed::Session>& session);
void put_issue_request(const std::shared_ptr<restbed::Session >&
                       session, const restbed::Bytes & body);
void put_issue_handler(const std::shared_ptr<restbed::Session>& session);
void parse_issue_put(const char* data, Issue*& issue, const unsigned int id);
void get_issue_handler(const std::shared_ptr<restbed::Session>& session);
void get_issue_by_id_handler(const std::shared_ptr<restbed::Session>& session);
void get_comment_handler(const std::shared_ptr<restbed::Session>& session);
void get_comment_by_id_handler(const std::shared_ptr<restbed::Session>& session);
bool readDB();
void writeDB();


/*++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*                  Variables                         */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++*/
std::map<int, User*> users;
std::map<int, Issue*> issues;
int userIDX = 0, issueIDX = 0;


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
    unsigned int id     = userIDX++;

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
 * @brief handles the POST request for the /users endpoint
 * @param session   current session between server and client
 */
void post_user_handler(const std::shared_ptr<restbed::Session>& session) {
    const auto request      = session->get_request();
    size_t content_length   = request->get_header("Content-Length", 0);
    session->fetch(content_length, &post_user_request);
}



/**
 * @brief handles the DELETE request for the /users/{id} endpoint
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
            message = "User successfully deleted";
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
 * @brief handles the GET request for the /users endpoint
 *        /users                lists all the users
 *        /users/{id}           list the specified user by id
 *        /users?group={val}    list user by group
 * @param session   current session between server and client
 */
void get_user_handler(const std::shared_ptr<restbed::Session>& session) {
    const auto request = session->get_request();
    std::fstream f("./db.json");
    json j = json::parse(f);
    json resultJSON;

    if ( request->has_path_parameter("id") ) {
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
        if ( request->has_query_parameter("group") ) {
            // search for all users that belong in a specified group
            std::string targetGroup = request->get_query_parameter("group");
            json collection = json::array(); // initialize to empty array
            for (auto &u : j["users"]) {
                std::string userGroup = User::getGroup(u["group"]);
                if (targetGroup == userGroup)
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

/* ++++++++++++++++++++++++++++++++++
    End of User functions
+++++++++++++++++++++++++++++++++++++ */

/* ++++++++++++++++++++++++++++++++++
    Issue functions
+++++++++++++++++++++++++++++++++++++ */
/**
 * @brief parses the string data and convert it to actual ISSUE object
 * @param data  actual data sent from the client
 * @param issue  ISSUE object to be filled with data members
 */
void parse_issue(const char* data, Issue*& issue) {
    // convert string to actual json obj
    json i = json::parse(data);

    // new issue gets an ID based on value of issueIDX
    unsigned int id     = issueIDX++;


    issue = new Issue(id, i["title"], users[i["author"]]);
    issue->setDescription(i["description"]);
    issue->setType(i["type"]);
    issue->setStatus(i["status"]);

    for (auto& a : i["assignees"])
        issue->addAssignee(users[a]);

    unsigned int commentID = 0;
    for (auto& c : i["comments"]) {
        issue->addComment(new Comment(0, users[c["author"]], c["comment"]));
    }
}


/**
 * @brief creates a new ISSUE object and inserts it into the users map
 *        closes the session after
 * @param session   current session between server and client
 * @param body      body of the request
 */
void post_issue_request(const std::shared_ptr<restbed::Session >&
                       session, const restbed::Bytes & body) {
    Issue* i;
    const char* data = reinterpret_cast<const char*>(body.data());
    parse_issue(data, i);

    nlohmann::json resultJSON;
    resultJSON["result"]    = "New issue is added";

    // info to be sent back to the client
    std::string response = resultJSON.dump();

    // info to be stored in the server
    issues.insert(std::make_pair(i->getID(), i));

    // update db
    writeDB();
    session->close(restbed::OK, response, { ALLOW_ALL, JSON, { "Content-Length", std::to_string(response.length()) }, CLOSE_CONNECTION });
}



/**
 * @brief handles the POST request for the /issues/ endpoint
 * @param session   current session between server and client
 */
void post_issue_handler(const std::shared_ptr<restbed::Session>& session) {
    const auto request      = session->get_request();
    size_t content_length   = request->get_header("Content-Length", 0);
    session->fetch(content_length, &post_issue_request);
}



/**
 * @brief parses the string data and convert it to actual ISSUE object
 * @param data  actual data sent from the client
 * @param issue  ISSUE object to be filled with data members
 * @param id    id of the issue to be updated
 */
void parse_issue_put(const char* data, Issue*& issue, const unsigned int id) {
    // convert string to actual json obj
    json i = json::parse(data)["issue"];

    //std::cout << i << std::endl;
    // search for the issue
    issue = issues.find((int)id)->second;

    // don't replace ID, they're meant to be just a reference
    issue->setTitle(i["title"]);
    issue->setDescription(i["description"]);
    issue->setType(i["type"]);
    issue->setStatus(i["status"]);
    issue->clearComments();

    for (auto& c : i["comments"]) {
        issue->addComment(new Comment(0, users[c["author"]], c["comment"]));
    }
}



/**
 * @brief updates the DB whenever the issue is updated
 * @param session   current session between server and client
 * @param body      body of the request
 */
void put_issue_request(const std::shared_ptr<restbed::Session >&
                       session, const restbed::Bytes & body) {
    const auto request   = session->get_request();
    const char* data     = reinterpret_cast<const char*>(body.data());
    std::string id       = request->get_path_parameter("issue_id");
    unsigned int issueID = std::stoul(id, nullptr, 10);

    Issue* i;
    parse_issue_put(data, i, issueID);

    nlohmann::json resultJSON;
    resultJSON["result"]    = "An issue is updated";

    // info to be sent back to the client
    std::string response = resultJSON.dump();

    // info to be stored in the server
    issues.erase((int)issueID);
    issues.insert(std::make_pair(i->getID(), i));

    // update db
    writeDB();
    session->close(restbed::OK, response, { ALLOW_ALL, JSON, { "Content-Length", std::to_string(response.length()) }, CLOSE_CONNECTION });
}





/**
 * @brief handles the PUT request for the /issues/{id} endpoint
 * @param session   current session between server and client
 */
void put_issue_handler(const std::shared_ptr<restbed::Session>& session) {
    const auto request      = session->get_request();
    size_t content_length   = request->get_header("Content-Length", 0);
    session->fetch(content_length, &put_issue_request);
}


/**
 * @brief handles the DELETE request for the /issues/{id} endpoint
 * @param session   current session between server and client
 */
void delete_issue_handler(const std::shared_ptr<restbed::Session>& session) {
    const auto request      = session->get_request();
    std::map<int, Issue*>::iterator it;
    std::string message;
    json resultJSON;

    if (request->has_path_parameter("issue_id")) {
        std::string paramID = request->get_path_parameter("issue_id");
        int targetID        = std::stoi(paramID);

        it = issues.find(targetID);
        if (it != issues.end()) {
            issues.erase(it);
            message = "Issue successfully deleted";
            writeDB();
        } else {
            message = "Issue not found";
        }

    } else {
        message = "Issue not found";
    }

    resultJSON["result"]    = message;
    std::string response    = resultJSON.dump();
    session->close(restbed::OK, response, { ALLOW_ALL, { "Content-Length", std::to_string(response.length()) }, CLOSE_CONNECTION });
}


/**
 * @brief handles the GET request for the /issue endpoint
 *        with query parameters
 *        Endpoints:
 *        /issues                     gets all the issues
 *        /issues?type=val            gets issues by type
 *        /issues?status=val          gets issues by status
 *        /issues?start=0&end=0       if start == end, then /issues/{start==val}
 *        /issues?start=3&end=0       if start > end, then return "result" : "No issues found"
 *        /issues?start=0&end=2       returns issues with id 0 through 2
 * @param session   current session between server and client
 */
void get_issue_handler(const std::shared_ptr<restbed::Session>& session) {
    const auto request = session->get_request();
    std::fstream f("./db.json");
    json j = json::parse(f);
    json resultJSON;
    bool withQuery = false;

    /*********************************************************** BY TYPE */
    if (request->has_query_parameter("type")) {
        std::string targetType = request->get_query_parameter("type");
        json collection = json::array();

        // search user based on type
        for (auto &i : j["issues"]) {
            std::string issueType = Issue::getTypeT(i["type"]);
            if (issueType == targetType)
                collection.push_back(i);
        }
        resultJSON["issues"] = collection;
        withQuery = true;
    }

    /********************************************************* BY STATUS */
    if ( request->has_query_parameter("status") ) {
        std::string targetStatus = request->get_query_parameter("status");
        json collection = json::array();

        // search user based on status
        for (auto &i : j["issues"]) {
            std::string issueStatus = Issue::getStatusT(i["status"]);
            if ( issueStatus == targetStatus )
                collection.push_back(i);
        }
        resultJSON["issues"] = collection;
        withQuery = true;
    }

    /********************************************************* BY RANGE */
    if ( request->has_query_parameter("start") && request->has_query_parameter("end") ) {
        std::string start     = request->get_query_parameter("start");
        std::string end       = request->get_query_parameter("end");
        unsigned int startID  = std::stoul(start, nullptr, 10);
        unsigned int endID    = std::stoul(end, nullptr, 10);
        json collection = json::array();

        if (startID > endID) {
            // startID > endID
            resultJSON["result"] = "Invalid parameters";
        } else if (startID == endID) {
            // startID == endID
            for (auto &i : j["issues"]) {
                unsigned int issueID = i["id"];
                if ( issueID == startID )
                    collection.push_back(i);
            }
            resultJSON["issues"] = collection;
        } else {
            // startID < endID
            for (auto &i : j["issues"]) {
                unsigned int issueID = i["id"];
                if ( issueID >= startID && issueID <= endID )
                    collection.push_back(i);
            }
            resultJSON["issues"] = collection;
        }
        withQuery = true;
    }


    /*********************************************** WITHOUT QUERY PARAM */
    if ( withQuery == false ) {
        resultJSON["issues"] = j["issues"];
    }

    f.close();
    std::string response = resultJSON.dump(4);
    session->close(restbed::OK, response, { ALLOW_ALL, { "Content-Length", std::to_string(response.length()) }, CLOSE_CONNECTION });
}


/**
 * @brief handles the GET request for the
 *        /issues/{issue_id} endpoint
 * @param session   current session between server and client
 */
void get_issue_by_id_handler(const std::shared_ptr<restbed::Session>& session) {
    const auto request = session->get_request();
    std::fstream f("./db.json");
    json j = json::parse(f);
    json resultJSON;

    // get the issue by ID
    if (request->has_path_parameter("issue_id")) {
        std::string targetID = request->get_path_parameter("issue_id");

        for (auto &i : j["issues"]) {
            int issueID = i["id"];
            if ( issueID == std::stoi(targetID) ) {
                resultJSON = i;
                break;
            }
        }

        if (resultJSON.empty())
            resultJSON["result"] = "No issue found";

    } else {
        resultJSON["result"] = "No issue found";
    }

    f.close();
    std::string response = resultJSON.dump(4);
    session->close(restbed::OK, response, { ALLOW_ALL, { "Content-Length", std::to_string(response.length()) }, CLOSE_CONNECTION });
}




/**
 * @brief handles the GET request for the
 *        /issues/{issue_id}/comments/ endpoint
 * @param session   current session between server and client
 */
void get_comment_handler(const std::shared_ptr<restbed::Session>& session) {
    const auto request = session->get_request();
    std::fstream f("./db.json");
    json j = json::parse(f);
    json resultJSON;
    json issue;

    // get the specific issue
    std::string targetIssueID = request->get_path_parameter("issue_id");
    for (auto &i : j["issues"]) {
        int issueID = i["id"];
        if (issueID == std::stoi(targetIssueID)) {
            issue = i;
            break;
        }
    }

    // get all the comments
    if (!issue.empty()) {
        resultJSON = issue["comments"];
    } else {
        resultJSON["result"] = "No issue found";
    }

    f.close();
    std::string response = resultJSON.dump(4);
    session->close(restbed::OK, response, { ALLOW_ALL, { "Content-Length", std::to_string(response.length()) }, CLOSE_CONNECTION });
}




/**
 * @brief handles the GET request for the
 *        /issues/{issues_id}/comments/{comment_id} endpoint
 * @param session   current session between server and client
 */
void get_comment_by_id_handler(const std::shared_ptr<restbed::Session>& session) {
    const auto request = session->get_request();
    std::fstream f("./db.json");
    json j = json::parse(f);
    json resultJSON;
    json issue;

    // get the specific issue
    std::string targetIssueID = request->get_path_parameter("issue_id");
    for (auto &i : j["issues"]) {
        int issueID = i["id"];
        if (issueID == std::stoi(targetIssueID)) {
            issue = i;
            break;
        }
    }

    // get the the comment by id
    if (!issue.empty()) {
        std::string targetCommentID = request->get_path_parameter("comment_id");
        for (auto &c : issue["comments"]) {
            int commentID = c["id"];
            if (commentID == std::stoi(targetCommentID)) {
                resultJSON = c;
                break;
            }
        }
        if (resultJSON.empty())
            resultJSON["result"] = "No comment found";
    } else {
        resultJSON["result"] = "No issue found";
    }

    f.close();
    std::string response = resultJSON.dump(4);
    session->close(restbed::OK, response, { ALLOW_ALL, { "Content-Length", std::to_string(response.length()) }, CLOSE_CONNECTION });
}

/* ++++++++++++++++++++++++++++++++++
    End of Issue functions
+++++++++++++++++++++++++++++++++++++ */





/*!
   \brief   reads the JSON file
   \pre     call this function in the main function to load all the objects
*/
bool readDB() {
    json j;
    std::fstream f("./db.json");
    std::string s;
    if (!(f >> s))
        return false;

    f.clear();
    f.seekg(0, std::ios::beg);
    j = json::parse(f);

    if (!j["userIDX"].is_null())
        userIDX  = j["userIDX"];
    if (!j["issueIDX"].is_null())
        issueIDX = j["issueIDX"];

    // create user objects
    if (!j["users"].is_null()) {
        for (auto &u : j["users"]) {
            User* user = new User(u["id"], u["name"]);
            user->setGroup(u["group"]);
            users.insert(std::make_pair(u["id"], user));
        }
    }

    // create issue objects
    if (!j["issues"].is_null()) {
        for (auto &i : j["issues"]) {
            Issue* issue = new Issue(i["id"], i["title"], users[i["author"]]);
            issue->setType(i["type"]);
            issue->setStatus(i["status"]);
            issue->setDescription(i["description"]);

            if (!i["assignees"].is_null()) {
                for (auto &a : i["assignees"])
                    issue->addAssignee(users[a]);
            }

            if (!i["comments"].is_null()) {
                for (auto &c : i["comments"])
                    issue->addComment(new Comment(c["id"], users[c["author"]], c["comment"]));
            }

            issues.insert(std::make_pair(i["id"], issue));
        }
    }

    f.close();
    return true;
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

    // Add issues to JSON object
    for (auto &i : issues) {
        json issue;
        issue["id"]          = i.second->getID();
        issue["title"]       = i.second->getTitle();
        issue["description"] = i.second->getDescription();
        issue["author"]      = i.second->getIssuer()->getID();
        issue["type"]        = i.second->getType();
        issue["status"]      = i.second->getStatus();
        issue["commentIDX"]  = i.second->getNumOfComments();
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
    f << std::setw(4) << j;
    f.close();
}



/*++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*                    MAIN FUNCTION                     */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

int main(const int, const char**) {
    readDB();
    std::cout << "users: " << std::to_string(users.size()) << std::endl;
    std::cout << "issues: " << std::to_string(issues.size()) << std::endl;

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

    auto resource_issue = std::make_shared<restbed::Resource>();
    resource_issue->set_path("/issues");
    resource_issue->set_method_handler("POST", { {"Accept", "application/json"}, {"Content-Type", "application/json"} }, &post_issue_handler);
    resource_issue->set_method_handler("GET", get_issue_handler);

    auto resource_issue_by_id = std::make_shared<restbed::Resource>();
    resource_issue_by_id->set_path("/issues/{issue_id: .*}");
    resource_issue_by_id->set_method_handler("GET", get_issue_by_id_handler);
    resource_issue_by_id->set_method_handler("PUT", { {"Accept", "application/json"}, {"Content-Type", "application/json"} }, &put_issue_handler);
    resource_issue_by_id->set_method_handler("DELETE", delete_issue_handler);

    auto resource_comments = std::make_shared<restbed::Resource>();
    resource_comments->set_path("/issues/{issue_id: .*}/comments");
    resource_comments->set_method_handler("GET", get_comment_handler);

    auto resource_comment_by_id = std::make_shared<restbed::Resource>();
    resource_comment_by_id->set_path("/issues/{issue_id: .*}/comments/{comment_id: .*}");
    resource_comment_by_id->set_method_handler("GET", get_comment_by_id_handler);


    auto settings = std::make_shared<restbed::Settings>();
    settings->set_port(1234);

    // Publish and start service
    restbed::Service service;
    service.publish(resource_users);
    service.publish(resource_user_by_id);
    service.publish(resource_issue);
    service.publish(resource_issue_by_id);
    service.publish(resource_comments);
    service.publish(resource_comment_by_id);

    service.start(settings);
    return EXIT_SUCCESS;
}
