#include <restbed>
#include <nlohmann/json.hpp>
#include <memory>
#include <string>
#include <future>
#include <cstdio>
#include <cstdlib>
#include <iostream>

/** Service information */
const char* HOST = "localhost";
const int PORT = 1234;

/** Server operations */
const char* NAME = "Billy";
const char* ISSUEMESSAGE = "I dont know how to use restbed";

std::shared_ptr<restbed::Request> create_post_request(const std::string& operation,
        const std::string& issue) {
    // Create the URI string
    std::string uri_str;
    uri_str.append("http://");
    uri_str.append(HOST);
    uri_str.append(":");
    uri_str.append(std::to_string(PORT));
    uri_str.append("/issues");

    // Configure request headers
    auto request = std::make_shared<restbed::Request>(restbed::Uri(uri_str));
    request->set_header("Accept", "*/*");
    request->set_method("POST");
    request->set_header("Content-Type", "text/plain");

    // Create the message
    std::string message;
    message.append(operation);
    message.append("\n");
    message.append("Created issue");

    // Set the message
    request->set_header("Content-Length", std::to_string(message.length()));
    request->set_body(message);

    return request;
}

std::shared_ptr<restbed::Request> create_get_request() {
    // Create the URI string
    std::string uri_str;
    uri_str.append("http://");
    uri_str.append(HOST);
    uri_str.append(":");
    uri_str.append(std::to_string(PORT));
    uri_str.append("/issues");


    //Configure request headers
    auto request = std::make_shared<restbed::Request>(restbed::Uri(uri_str));
    request->set_method("GET");

    // Set the parameters
    // request->set_query_parameter("name", operation);
    // request->set_query_parameter("issueMessage", issue);

    return request;
}


void handle_response(std::shared_ptr<restbed::Response> response) {
    int status_code = response->get_status_code();
    auto length = response->get_header("Content-Length", 0);
    switch (status_code) {
    case 200: {
        restbed::Http::fetch(length, response);
        std::string responseStr(reinterpret_cast<char*>(response->get_body().data()), length);

        nlohmann::json resultJSON = nlohmann::json::parse(responseStr);
        // std::string result = resultJSON["issues"];

        std::cout << resultJSON["issues"] << std::endl;
        break;
    }
    default:
        fprintf(stderr,
                 "My milk shakes bring all the boys to the yard\n");
        break;
    }
}

int main(const int, const char**) {
    std::shared_ptr<restbed::Request> request = create_post_request(NAME, ISSUEMESSAGE);
    auto response = restbed::Http::sync(request);
    handle_response(response);


    request = create_get_request();
    response = restbed::Http::sync(request);
    handle_response(response);

    return EXIT_SUCCESS;
}
