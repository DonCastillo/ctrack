#include <restbed>
#include <nlohmann/json.hpp>
#include <cstring>
#include <cstdlib>
#include <memory>
#include <string>

struct issue {
    std::string name;
    std::string issueMessage;
};

// Response header to prevent a cross-site validation problem
#define ALLOW_ALL { "Access-Control-Allow-Origin", "*" }

// Response header to close connection
#define CLOSE_CONNECTION { "Connection", "close" }

void parse(const char* data, issue* expr) {
    char* data_mutable = const_cast<char*>(data);
    char* a = strtok_r(nullptr, "\n", &data_mutable);
    char* b = strtok_r(nullptr, "\n", &data_mutable);

    expr->name = a;
    expr->issueMessage = b;
}


void post_request(const std::shared_ptr<restbed::Session >&
                  session, const restbed::Bytes & body) {
    issue exp;
    const char* data = reinterpret_cast<const char*>(body.data());
    parse(data, &exp);
    std::string resultStr = exp.name + " " + exp.issueMessage;
    nlohmann::json resultJSON;
    resultJSON["result"] = resultStr;
    std::string response = resultJSON.dump();

    session->close(restbed::OK, response, { ALLOW_ALL, { "Content-Length", std::to_string(response.length()) }, CLOSE_CONNECTION });
}


void post_method_handler(const std::shared_ptr<restbed::Session>& session) {
    const auto request = session->get_request();
    size_t content_length = request->get_header("Content-Length", 0);
    session->fetch(content_length, &post_request);
}

void get_method_handler(const std::shared_ptr<restbed::Session>& session) {
    const auto request = session->get_request();

    issue exp;

    if (request->has_query_parameter("name")) {
        exp.name = request->get_query_parameter("name");
        if (request->has_query_parameter("issueMessage")) {
            exp.issueMessage = request->get_query_parameter("issueMessage");
        }
    }

    std::string resultStr = exp.name + "\n" + exp.issueMessage;
    nlohmann::json resultJSON;
    resultJSON["result"] =  resultStr;
    std::string response = resultJSON.dump();

    session->close(restbed::OK, response, { ALLOW_ALL, { "Content-Length", std::to_string(response.length()) }, CLOSE_CONNECTION });
}

int main(const int, const char**) {
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
