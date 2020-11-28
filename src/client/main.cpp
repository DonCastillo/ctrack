#include <restbed>
#include <nlohmann/json.hpp>
#include <memory>
#include <string>
#include <future>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include "../../include/service/Comment.h"
#include "../../include/service/Issue.h"
#include "../../include/service/User.h"
#include "../../include/service/CTrackUI.h"

using json = nlohmann::json;

/** Service information */
const char* HOST = "localhost";
const int PORT = 1234;
std::vector<User*> users;

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
    request->set_header("Accept", "*/*");
    request->set_method("POST");
    request->set_header("Content-Type", "text/plain");

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
std::shared_ptr<restbed::Request> delete_request_by_user_id(std::string path) {
    // Create the URI string
    std::string uri = create_uri(path);

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

    //std::cout << std::to_string(status_code);

    switch (status_code) {
    case 200: {
        restbed::Http::fetch(length, response);
        std::string responseStr(reinterpret_cast<char*>(response->get_body().data()), length);
        nlohmann::json resultJSON = nlohmann::json::parse(responseStr);
        std::cout << resultJSON;
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

        switch(choice) {

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
                request = get_request_by_path("/users");
                auto response_user = restbed::Http::sync(request);
                handle_response_user(response_user);
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
        case 1:
            //ui->viewIssue();
            break;
        case 2:
            //ui->deleteIssue();
            break;
        case 3:
            //ui->editIssue();
            break;
        case 4: {
                User* dummyUser = ui->createUser();
                request       = create_user_post_request(dummyUser);
                auto response = restbed::Http::sync(request);
                handle_response(response);
                delete dummyUser;
                }
            break;
        case 5: {
                path          = ui->viewUser();
                request       = get_request_by_path(path);
                auto response = restbed::Http::sync(request);
                handle_response(response);
                }
            break;
        case 6: {
                path          = ui->deleteUser();
                request       = delete_request_by_user_id(path);
                auto response = restbed::Http::sync(request);
                handle_response(response);
                break;
                }
        }

        cont = ui->continueUsing();

    } while (cont);

    delete ui;
    return EXIT_SUCCESS;
}
