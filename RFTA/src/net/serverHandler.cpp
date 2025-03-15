#include "../../header/net/serverHandler.h"
#include <iostream>

ServerHandler::Result ServerHandler::getServers(std::string tokenEntry) {
    token = tokenEntry;
    httplib::Client cl("https://77.37.246.6:7777");
    cl.enable_server_certificate_verification(false);
    std::string endpoint = "api/servers";
    if (auto res = cl.Get(endpoint)) {
        if (res->status != 200) {
            return {res->status, res->body};
        } else {
            return {res->status, res->body};
        }
    } else {
        auto err = res.error();
        std::cout << httplib::to_string(err) << std::endl;
    }
}
