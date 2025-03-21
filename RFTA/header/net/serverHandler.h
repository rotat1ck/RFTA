#ifndef SERVERHANDLER_H
#define SERVERHANDLER_H

#define CPPHTTPLIB_OPENSSL_SUPPORT
#include <QObject>
#include "../utils/json.hpp"
#include "../utils/httplib.h"
#include <vector>

using json = nlohmann::json;

class ServerHandler : public QObject {
    Q_OBJECT

private:
    httplib::Client cl;

    struct Result {
        int status;
        std::string message;
    };

public:
    struct Server {
        int id;
        std::string name;
        std::string core;
        std::string version;
        bool status;
    };

    std::string token;

    std::vector<Server> servers;

    ServerHandler() : cl("https://77.37.246.6:7777") {
        cl.enable_server_certificate_verification(false);
        cl.set_connection_timeout(0, 500000);
    }

    Result getServers(std::string tokenEntry);
};

#endif // SERVERHANDLER_H
