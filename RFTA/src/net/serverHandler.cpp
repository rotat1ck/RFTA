#include "../../header/net/serverHandler.h"

ServerHandler::Result ServerHandler::getServers(std::string tokenEntry) {
    token = tokenEntry;
    cl.set_default_headers({{"Authorization", "Bearer " + token}});

    std::string endpoint = "api/servers/";
    if (auto res = cl.Get(endpoint)) {
        if (res->status != 200) {
            return {res->status, res->body};
        } else {
            return {res->status, res->body};
        }
    } else {
        return {0, ""};
    }
}
