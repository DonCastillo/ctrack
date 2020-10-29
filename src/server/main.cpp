#include <restbed>
#include <cstring>
#include <cstdlib>
#include <memory>
#include <string>
#include <nlohmann/json.hpp>
#include "../../include/service/Comment.h"
#include "../../include/service/Issue.h"
#include "../../include/service/User.h"

// Response header to prevent a cross-site validation problem
#define ALLOW_ALL { "Access-Control-Allow-Origin", "*" }

// Response header to close connection
#define CLOSE_CONNECTION { "Connection", "close" }

/**
* POST request callback function.
*/
void post_request(const std::shared_ptr<restbed::Session >&
                  session, const restbed::Bytes & body) {
    // expression exp;
    // const char* data = reinterpret_cast<const char*>(body.data());
    // parse(data, &exp);
    // compute(exp, session);
}

/**
* Handle a POST request.
* @param session The request session.
*/
void post_method_handler(const std::shared_ptr<restbed::Session>& session) {
    // const auto request = session->get_request();
    // size_t content_length = request->get_header("Content-Length", 0);
    // session->fetch(content_length, &post_request);
}

/**
* Handle a GET request.
* @param session The request session.
*/
void get_method_handler(const std::shared_ptr<restbed::Session>& session) {
    // const auto request = session->get_request();

    // expression exp;
    // exp.op = UNKNOWN;
    // exp.first = 0;
    // exp.second = 0;

    // if (request->has_query_parameter("op")) {
    //     set_operation(&exp, request->get_query_parameter("op").c_str());
    //     if (request->has_query_parameter("first")) {
    //         exp.first = stod(request->get_query_parameter("first"));
    //     }
    //     if (request->has_query_parameter("second")) {
    //         exp.second = stod(request->get_query_parameter("second"));
    //     }
    // }

    // compute(exp, session);
}

void readDB(std::vector<User*>* users, std::vector<Issue*>* issues) {
}

int main(const int, const char**) {
    std::vector<User*> users;
    std::vector<Issue*> issues;
    readDB(&users, &issues);

    // Setup service and request handlers
    auto resource = std::make_shared<restbed::Resource>();
    resource->set_path("/issues");
    resource->set_method_handler("POST", post_method_handler);
    resource->set_method_handler("GET", get_method_handler);

    auto settings = std::make_shared<restbed::Settings>();
    settings->set_port(1234);

    // Publish and start service
    restbed::Service service;
    service.publish(resource);

    service.start(settings);
    return EXIT_SUCCESS;
}
