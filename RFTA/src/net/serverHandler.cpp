#include "../../header/net/serverHandler.h"

bool ServerHandler::checkToken() {
    cl.set_default_headers({{"Authorization", "Bearer " + token}});
    std::string endpoint = "api/users/healthcheck";

    if (auto res = cl.Get(endpoint)) {
        if (res->status == 200) {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

ServerHandler::Result ServerHandler::getServers() {
    cl.set_default_headers({{"Authorization", "Bearer " + token}});

    std::string endpoint = "api/servers/";
    if (auto res = cl.Get(endpoint)) {
        return {res->status, res->body};
    } else {
        return {0, ""};
    }
}

ServerHandler::Result ServerHandler::getModPack(int serverId) {
    cl.set_default_headers({{"Authorization", "Bearer " + token}});
}
