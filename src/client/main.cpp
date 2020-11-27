#include <restbed>
#include <nlohmann/json.hpp>
#include <memory>
#include <string>
#include <future>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "../../include/service/Comment.h"
#include "../../include/service/Issue.h"
#include "../../include/service/User.h"
#include "../../include/service/CTrackUI.h"

/** Service information */
const char* HOST = "localhost";
const int PORT = 1234;


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


std::shared_ptr<restbed::Request> delete_request_by_user_id(std::string path) {
    // Create the URI string
    std::string uri = create_uri(path);

    //Configure request headers
    auto request = std::make_shared<restbed::Request>(restbed::Uri(uri));
    request->set_method("DELETE");

    return request;
}




void handle_response(std::shared_ptr<restbed::Response> response) {
    int status_code = response->get_status_code();
    auto length     = response->get_header("Content-Length", 0);

    std::cout << std::to_string(status_code);
    /**
        200     OK
        400     BAD REQUEST
        404     NOT FOUND
        500     INTERNAL SERVER ERROR
    */
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




int main(const int, const char**) {

// @todo create a ui to enable clients to dynamically CRUD records

   std::string path;
   unsigned int id;

    User* dummyUser         = nullptr;
    Issue* dummyIssue       = nullptr;
    Comment* dummyComment   = nullptr;
    CTrackUI* ui = new CTrackUI();

    unsigned int choice;
    bool cont = false;
    std::shared_ptr<restbed::Request> request;

    // do {
    //     ui->welcome();
    //     choice = ui->menu();
    //
    //     switch(choice) {
    //     case 0:
    //         //ui->createIssue();
    //         break;
    //     case 1:
    //         //ui->viewIssue();
    //         break;
    //     case 2:
    //         //ui->deleteIssue();
    //         break;
    //     case 3:
    //         //ui->editIssue();
    //         break;
    //     case 4: {
    //         dummyUser = ui->createUser();
    //         request = create_user_post_request(dummyUser);
    //         }
    //         break;
    //     case 5: {
    //         path = ui->viewUser();
    //         request = get_request_by_path(path);
    //         }
    //         break;
    //     case 6:
    //         path = ui->deleteUser();
    //         request = delete_request_by_user_id(path);
    //         break;
    //     }
    //
    //     auto response = restbed::Http::sync(request);
    //     handle_response(response);
    //     cont = ui->continueUsing();
    //
    // } while (cont);





   // Create new user record
//   User* dummyUser = new User(0, "Dustin Ward");
//   std::shared_ptr<restbed::Request> request = create_user_post_request(dummyUser);
//   auto response = restbed::Http::sync(request);
//   handle_response(response);

   //list all users
   path = "/issues";
   request = get_request_by_path(path);
   auto response = restbed::Http::sync(request);
   handle_response(response);

   //look for a specific user
   id = 0;
   path = "/issues/"+std::to_string(id);
   request = get_request_by_path(path);
   response = restbed::Http::sync(request);
   handle_response(response);

   // list users that match a query
   // request = get_request_by_user_query(dummyUser);
   // response = restbed::Http::sync(request);
   // handle_response(response);

   // delete a user based on specified ID
//   id = 7;
//   std::shared_ptr<restbed::Request> request = delete_request_by_user_id(id);
//   auto response = restbed::Http::sync(request);
//   handle_response(response);

   return EXIT_SUCCESS;
}
