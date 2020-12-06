#include <nlohmann/json.hpp>
#include <restbed>
#include <memory>
#include <string>
#include <future>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <map>
#include <utility>
#include "../../include/service/Comment.h"
#include "../../include/service/Issue.h"
#include "../../include/service/User.h"
#include "../../include/service/CTrackUI.h"

using json = nlohmann::json;

/** Service information */
const char* HOST = "localhost";
const int PORT = 1234;
std::vector<User*> users;
std::vector<Issue*> issues;

/*++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*                General functions                   */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++*/
std::string create_uri(std::string endpoint) {
    std::string uri_str;
    uri_str.append("http://");
    uri_str.append(HOST);
    uri_str.append(":");
    uri_str.append(std::to_string(PORT));
    uri_str.append("/");
    uri_str.append(endpoint);
    return uri_str;
}


User* getUser(unsigned int pID) {
    for (User* u : users) {
        if (pID == u->getID()) {
            return u;
        }
    }
    return nullptr;
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*                  POST Functions                    */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++*/
std::shared_ptr<restbed::Request> create_user_post_request(const User* user) {
    // Create the URI string
    std::string uri = create_uri("users");

    // Configure request headers
    auto request = std::make_shared<restbed::Request>(restbed::Uri(uri));
    request->set_header("Accept", "*/*");
    request->set_method("POST");
    request->set_header("Content-Type", "text/plain");

    // Create the message
    std::string message;
    message.append(user->getName());
    message.append("\n");
    message.append(std::to_string(user->getGroup()));

    // Set the message
    request->set_header("Content-Length", std::to_string(message.length()));
    request->set_body(message);

    return request;
}



std::shared_ptr<restbed::Request> create_issue_post_request(const Issue* dummyIssue) {
    // Create the URI string
    std::string uri = create_uri("issues");

    // Configure request headers
    auto request = std::make_shared<restbed::Request>(restbed::Uri(uri));
    request->set_header("Accept", "application/json");
    request->set_method("POST");
    request->set_header("Content-Type", "application/json");
    //request->set_header("X-Content-Type-Options", "nosniff");
    //request->set_header("Accept-Charset", "utf-8");

    // Create the message
    json issue;
    issue["title"]        = dummyIssue->getTitle();
    issue["description"]  = dummyIssue->getDescription();
    issue["author"]       = dummyIssue->getIssuer()->getID();
    issue["type"]         = dummyIssue->getTypeInt();
    issue["status"]       = dummyIssue->getStatusInt();
    issue["assignees"]    = json::array();
    issue["comments"]     = json::array();

    for (User* u : dummyIssue->getAssignees())
        issue["assignees"].push_back(u->getID());

    for (Comment* c : dummyIssue->getComments()) {
        json comment;
        comment["author"]   = c->getCommenter()->getID();
        comment["comment"]  = c->getComment();
        issue["comments"].push_back(comment);
    }

    std::string message = issue.dump();

    // Set the message
    request->set_header("Content-Length", std::to_string(message.length()));
    request->set_body(message);

    return request;
}

/*++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*                  PUT Functions                     */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++*/

std::shared_ptr<restbed::Request> create_issue_put_request(const Issue* dummyIssue) {
    // Create the URI string
    std::string uri = create_uri("issues/" + std::to_string(dummyIssue->getID()));

    // Configure request headers
    auto request = std::make_shared<restbed::Request>(restbed::Uri(uri));
    request->set_header("Accept", "application/json");
    request->set_method("PUT");
    request->set_header("Content-Type", "application/json");
    //request->set_header("X-Content-Type-Options", "nosniff");
    //request->set_header("Accept-Charset", "utf-8");

    // Create the message
    json issue;
    issue["issue"]["title"]        = dummyIssue->getTitle();
    issue["issue"]["description"]  = dummyIssue->getDescription();
    issue["issue"]["type"]         = dummyIssue->getTypeInt();
    issue["issue"]["status"]       = dummyIssue->getStatusInt();
    issue["issue"]["comments"]     = json::array();

    //std::cout << "working here" << std::endl;

    for (Comment* c : dummyIssue->getComments()) {
        json comment;
        comment["author"]   = c->getCommenter()->getID();
        comment["comment"]  = c->getComment();
        issue["issue"]["comments"].push_back(comment);
    }

    std::string message = issue.dump();
    //std::cout << message << std::endl;

    // Set the message
    request->set_header("Content-Length", std::to_string(message.length()));
    request->set_body(message);

    return request;
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*                  GET Functions                     */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++*/
std::shared_ptr<restbed::Request> get_request_by_path(std::string path) {
    // Create the URI string
    std::string uri = create_uri(path);

    //Configure request headers
    auto request = std::make_shared<restbed::Request>(restbed::Uri(uri));
    request->set_method("GET");

    return request;
}


std::shared_ptr<restbed::Request> get_request_by_user_query(User* pUser) {
    // Create the URI string
    std::string uri = create_uri("users");

    //Configure request headers
    auto request = std::make_shared<restbed::Request>(restbed::Uri(uri));
    request->set_method("GET");

    // Set the parameters
    request->set_query_parameter("group",  pUser->getGroupString());

    return request;
}

/*++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*                DELETE Functions                    */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++*/
std::shared_ptr<restbed::Request> delete_request_by_id(std::string path) {
    // Create the URI string
    std::string uri = create_uri(path);
    std::cout << uri << std::endl;

    //Configure request headers
    auto request = std::make_shared<restbed::Request>(restbed::Uri(uri));
    request->set_method("DELETE");

    return request;
}



/*++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*        Handle Response Functions                   */
/*        200       OK                                */
/*        400       BAD REQUEST                       */
/*        404       NOT FOUND                         */
/*        500       INTERNAL SERVER ERROR             */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void handle_response(std::shared_ptr<restbed::Response> response) {
    int status_code = response->get_status_code();
    auto length     = response->get_header("Content-Length", 0);

    std::cout << std::to_string(status_code) << std::endl;

    switch (status_code) {
    case 200: {
        restbed::Http::fetch(length, response);
        std::string responseStr(reinterpret_cast<char*>(response->get_body().data()), length);
        nlohmann::json resultJSON = nlohmann::json::parse(responseStr);
        std::cout << resultJSON.dump(4);
        break;
    }
    case 400:
    case 404: {
        restbed::Http::fetch(length, response);
        fprintf(stderr, "Error: %.*s\n", length, response->get_body().data());
        break;
    }
    default:
        fprintf(stderr, "There is an error connecting to the server. \n Try again.");
        break;
    }
}

void handle_response_user(std::shared_ptr<restbed::Response> response) {
    int status_code = response->get_status_code();
    auto length     = response->get_header("Content-Length", 0);

    //std::cout << std::to_string(status_code);
    users.clear();

    switch (status_code) {
    case 200: {
        restbed::Http::fetch(length, response);
        std::string responseStr(reinterpret_cast<char*>(response->get_body().data()), length);
        nlohmann::json resultJSON = nlohmann::json::parse(responseStr);

        // store json as user objects and prints them
        for (auto &u : resultJSON["users"]) {
            User* myUser = new User(u["id"], u["name"]);
            myUser->setGroup(u["group"]);
            users.push_back(myUser);
        }
        break;
    }
    case 400:
    case 404: {
        restbed::Http::fetch(length, response);
        fprintf(stderr, "Error: %.*s\n", length, response->get_body().data());
        break;
    }
    default:
        fprintf(stderr, "There is an error connecting to the server. \n");
        break;
    }
}


void handle_response_issue(std::shared_ptr<restbed::Response> response) {
    int status_code = response->get_status_code();
    auto length     = response->get_header("Content-Length", 0);

    std::cout << std::to_string(status_code);
    issues.clear();

    switch (status_code) {
    case 200: {
        restbed::Http::fetch(length, response);
        std::string responseStr(reinterpret_cast<char*>(response->get_body().data()), length);
        nlohmann::json resultJSON = nlohmann::json::parse(responseStr);

        // store json as issue objects and prints them
        // make the issuer of this issue null. we don't need it to be changed when the issue gets updated.
        for (auto &i : resultJSON["issues"]) {
            Issue* myIssue = new Issue(i["id"], i["title"], nullptr);
            myIssue->setType(i["type"]);
            myIssue->setStatus(i["status"]);
            myIssue->setDescription(i["description"]);
            //myIssue->setNumOfComments(i["commentIDX"]);

            // assignees cannot be updated
            // we don't need edit the assignees
            for (auto &a : i["assignees"]) {
                //User* thisUser = getUser(a);
                myIssue->addAssignee(nullptr);
            }

            // make the commenter of this issue null. we don't need it to be changed when the issue gets updated.
            for (auto& c : i["comments"]) {
                User* thisUser = getUser(c["author"]);
                myIssue->addComment(new Comment(c["id"], thisUser, c["comment"]));
            }

            issues.push_back(myIssue);
        }
        break;
    }
    case 400:
    case 404: {
        restbed::Http::fetch(length, response);
        fprintf(stderr, "Error: %.*s\n", length, response->get_body().data());
        break;
    }
    default:
        fprintf(stderr, "There is an error connecting to the server. \n");
        break;
    }
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*                    MAIN FUNCTION                     */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
int main(const int, const char**) {
    std::string path;
    unsigned int id;


    Issue* dummyIssue       = nullptr;
    Comment* dummyComment   = nullptr;
    CTrackUI* ui = new CTrackUI();

    unsigned int choice;
    bool cont = false;
    std::shared_ptr<restbed::Request> request;

    do {
        ui->welcome();
        choice = ui->menu();

        // fetch all the users
        request = get_request_by_path("users");
        auto response_user = restbed::Http::sync(request);
        handle_response_user(response_user);

        // fetch all the issues
        request = get_request_by_path("issues");
        auto response_issue = restbed::Http::sync(request);
        handle_response_issue(response_issue);
        switch (choice) {
        case 0: {
                /*
                    The objects generated by the UI are dummy objects.
                    whose data are null except for the ID which is important
                    to reference a specific object in the server
                */
                ui->printTitle("CREATING AN ISSUE");
                // ask issue title
                std::string issueTitle = ui->askIssueTitle();
                // ask issue description
                std::string issueDesc  = ui->askIssueDescription();

                // ask user ID to be assigned as issuer/author
                ui->println("Enter the ID of the user");
                ui->print("you want as an author of this issue.\n");

                User* issuer           = ui->askWhichUser(users);

                // ask issue type
                unsigned int type      = ui->askIssueType();
                // ask issue status
                unsigned int status    = ui->askIssueStatus();
                // ask for a list of assignees of this issue
                std::vector<User*> assignees;
                assignees              = ui->askIssueAssignees(users);
                // ask for a list of comments of this issue
                ui->printTitle("ADDING COMMENTS");
                ui->println("Enter the ID of the user");
                ui->print("you want as an author of this comment.\n");
                std::vector<Comment*> comments;
                comments               = ui->askIssueComments(users);
                // create a dummy user object based on entered data
                dummyIssue             = new Issue(0, issueTitle, issuer);
                dummyIssue->setDescription(issueDesc);
                dummyIssue->setType(type);
                dummyIssue->setStatus(status);
                for (User* u : assignees)
                    dummyIssue->addAssignee(u);
                for (Comment* c : comments)
                    dummyIssue->addComment(c);
                ui->println("\nUser Preview");
                std::cout << *dummyIssue;
                // call POST request
                request                = create_issue_post_request(dummyIssue);
                auto response          = restbed::Http::sync(request);
                handle_response(response);
                delete dummyIssue;
                delete issuer;
                }
            break;
        case 1: {
                ui->printTitle("VIEWING AN ISSUE");
                path          = ui->viewIssue();
                request       = get_request_by_path(path);
                auto response = restbed::Http::sync(request);
                handle_response(response);
                }
            break;
        case 2: {
                ui->printTitle("DELETING AN ISSUE");
                ui->println("Which issue to delete?");
                std::map<unsigned int, std::string> issueMap;
                for (Issue* i : issues)
                    issueMap.insert(std::pair<unsigned int, std::string>(i->getID(), i->getTitle()));
                unsigned int issueID  = ui->choose(issueMap);
                request       = delete_request_by_id("issues/" + std::to_string(issueID));
                auto response = restbed::Http::sync(request);
                handle_response(response);
                }
            break;
        case 3: {
                ui->printTitle("EDITING AN ISSUE");
                // fetch all the users
                request = get_request_by_path("users");
                auto response_user = restbed::Http::sync(request);
                handle_response_user(response_user);
                // fetch all the issues
                request = get_request_by_path("issues");
                auto response_issue = restbed::Http::sync(request);
                handle_response_issue(response_issue);


                // ask issue ID to edit
                // referenceIssue is a dummy issue with no real data
                // except for the ID chosen by the user
                Issue* referenceIssue      =   ui->askWhichIssue(issues);
                Issue* dummyIssue;  // actual object chosen

                for (Issue* i : issues) {
                    if ( referenceIssue->getID() == i->getID() )
                        dummyIssue = i;
                }

                delete referenceIssue;
                // print the actual issue chosen
                ui->println("Issue to be edited");
                ui->printRow("Issue ID", std::to_string(dummyIssue->getID()));
                ui->printRow("Issue Title", dummyIssue->getTitle());

                // ask which property to edit
                unsigned int propertyID    =   ui->askWhichIssueProperty();

                    switch (propertyID) {
                        case 0: {
                                ui->print("UPDATING TITLE\n");
                                ui->printRow("Current title", dummyIssue->getTitle());
                                std::string newTitle = ui->askIssueTitle();
                                dummyIssue->setTitle(newTitle);
                                ui->printRow("New title", dummyIssue->getTitle());
                                request                = create_issue_put_request(dummyIssue);
                                auto response          = restbed::Http::sync(request);
                                handle_response(response);
                                delete dummyIssue;
                                }
                            break;
                        case 1: {
                                ui->print("UPDATING DESCRIPTION\n");
                                ui->println("Current description: " + dummyIssue->getDescription());
                                std::string newDesc = ui->askIssueDescription();
                                dummyIssue->setDescription(newDesc);
                                ui->println("New description: " + dummyIssue->getDescription());
                                request                = create_issue_put_request(dummyIssue);
                                auto response          = restbed::Http::sync(request);
                                handle_response(response);
                                delete dummyIssue;
                                }
                            break;
                        case 2: {
                                ui->print("UPDATING STATUS\n");
                                ui->println("Current status: " + dummyIssue->getStatusString());
                                unsigned int newStatus = ui->askIssueStatus();
                                dummyIssue->setStatus(newStatus);
                                ui->println("New status: " + dummyIssue->getStatusString());
                                request                = create_issue_put_request(dummyIssue);
                                auto response          = restbed::Http::sync(request);
                                handle_response(response);
                                delete dummyIssue;
                                }
                            break;
                        case 3: {
                                ui->print("UPDATING TYPE\n");
                                ui->println("Current type: " + dummyIssue->getTypeString());
                                unsigned int newType = ui->askIssueType();
                                dummyIssue->setType(newType);
                                ui->println("New type: " + dummyIssue->getTypeString());
                                request                = create_issue_put_request(dummyIssue);
                                auto response          = restbed::Http::sync(request);
                                handle_response(response);
                                delete dummyIssue;
                                }
                            break;
                        case 4: {
                                bool continueCommenting;
                                do {
                                    ui->print("UPDATING COMMENT\n");
                                    unsigned int updateID = ui->updateCommentAction();
                                    switch (updateID) {
                                        case 0: {
                                                ui->println("ADDING COMMENT");
                                                std::vector<Comment*> newComments;
                                                ui->println("Choose a commenter.");
                                                unsigned int numOfComments = dummyIssue->getNumOfComments();
                                                newComments = ui->askIssueComments(users);
                                                std::cout << newComments.size() << std::endl;
                                                for (Comment* c : newComments) {
                                                    std::cout << c->getComment() << std::endl;
                                                    dummyIssue->addComment(c);
                                                }
                                                ui->println(std::to_string(newComments.size()) + " new comments added.");
                                                request                = create_issue_put_request(dummyIssue);
                                                auto response          = restbed::Http::sync(request);
                                                handle_response(response);
                                                }
                                            break;
                                        case 1: {
                                                ui->println("DELETING COMMENT");
                                                Comment* chosenComment = ui->askWhichComment(dummyIssue->getComments());
                                                bool success = dummyIssue->deleteComment(chosenComment->getID());
                                                if (success)
                                                    ui->println("1 comment deleted.");
                                                else
                                                    ui->println("Comment deletion failed");
                                                request                = create_issue_put_request(dummyIssue);
                                                auto response          = restbed::Http::sync(request);
                                                handle_response(response);
                                                }
                                            break;
                                        case 2: {
                                                ui->println("EDITING A COMMENT");
                                                Comment* chosenComment = ui->askWhichComment(dummyIssue->getComments());
                                                unsigned int newCommentID = chosenComment->getID(); // retain id
                                                dummyIssue->deleteComment(newCommentID);

                                                std::string newComment = ui->askComment();
                                                ui->println("Choose a commenter.");
                                                User* newCommenter = ui->askWhichUser(users);
                                                // add altered comment with same id
                                                //unsigned int prevNumOfComments = dummyIssue->getNumOfComments();
                                                dummyIssue->addComment(new Comment(newCommentID, newCommenter, newComment));
                                                request                = create_issue_put_request(dummyIssue);
                                                auto response          = restbed::Http::sync(request);
                                                handle_response(response);
                                                }
                                            break;
                                        }
                                  continueCommenting = ui->continueAddingComment();
                                } while ( continueCommenting == 1);
                                delete dummyIssue;
                                }
                                break;
                            }
                }
            break;
        case 4: {
                ui->printTitle("CREATING A USER");
                User* dummyUser = ui->createUser();
                request       = create_user_post_request(dummyUser);
                auto response = restbed::Http::sync(request);
                handle_response(response);
                delete dummyUser;
                }
            break;
        case 5: {
                ui->printTitle("VIEWING A USER");
                path          = ui->viewUser();
                request       = get_request_by_path(path);
                auto response = restbed::Http::sync(request);
                handle_response(response);
                }
            break;
        case 6: {
                ui->printTitle("DELETING A USER");
                ui->println("Not Implemented");
                // ui->println("Which user to delete?");
                // std::map<unsigned int, std::string> userMap;
                // for (User* u : users)
                //     userMap.insert(std::pair<unsigned int, std::string>(u->getID(), u->getName()));
                // unsigned int userID  = ui->choose(userMap);
                // request       = delete_request_by_id("users/" + std::to_string(userID));
                // auto response = restbed::Http::sync(request);
                // handle_response(response);
                }
            break;
        }

        cont = ui->continueUsing();
    } while (cont);

    delete ui;
    return EXIT_SUCCESS;
}
