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

/** Service information */
const char* HOST = "localhost";
const int PORT = 1234;

/** Server operations */


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


std::shared_ptr<restbed::Request> create_user_post_request(User* user) {
    // Create the URI string
    std::string uri = create_uri("users");

    // Configure request headers
    auto request = std::make_shared<restbed::Request>(restbed::Uri(uri));
    request->set_header("Accept", "*/*");
    request->set_method("POST");
    request->set_header("Content-Type", "text/plain");

    // Create the message
    std::string message;
    message.append( user->getName() );
    message.append("\n");
    message.append( std::to_string(user->group) );

    // Set the message
    request->set_header("Content-Length", std::to_string(message.length()));
    request->set_body(message);

    return request;
}



std::shared_ptr<restbed::Request> create_user_get_request(User* user) {
    // Create the URI string
    std::string uri = create_uri("users");

    //Configure request headers
    auto request = std::make_shared<restbed::Request>(restbed::Uri(uri));
    request->set_method("GET");

    // Set the parameters
    request->set_query_parameter("id",      std::to_string(user->getID()));
    request->set_query_parameter("name",    user->getName());
    request->set_query_parameter("group",   user->getGroup());

    return request;
}




void handle_response(std::shared_ptr<restbed::Response> response) {
    int status_code = response->get_status_code();
    auto length     = response->get_header("Content-Length", 0);

    std::cout << std::to_string(status_code);

    switch (status_code) {
    case 200: {
        restbed::Http::fetch(length, response);
        std::string responseStr(reinterpret_cast<char*>(response->get_body().data()), length);

        nlohmann::json resultJSON = nlohmann::json::parse(responseStr);
        std::cout << resultJSON;
        break;
    }
    default:
        fprintf(stderr, "My milk shakes bring all the boys to the yard\n");
        break;
    }
}




int main(const int, const char**) {
    User* user = new User(0, "Don Castillo");
    std::shared_ptr<restbed::Request> request = create_user_post_request(user);
    auto response = restbed::Http::sync(request);
    handle_response(response);

   request = create_user_get_request(user);
   response = restbed::Http::sync(request);
   handle_response(response);

   return EXIT_SUCCESS;
}
