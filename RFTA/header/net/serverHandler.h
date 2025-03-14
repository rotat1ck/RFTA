#ifndef SERVERHANDLER_H
#define SERVERHANDLER_H

#define CPPHTTPLIB_OPENSSL_SUPPORT
#include <QObject>
#include "../utils/json.hpp"
#include "../utils/httplib.h"

using json = nlohmann::json;

class ServerHandler : public QObject {
    Q_OBJECT

private:
    struct ServerList {
        int id;
        std::string name;
        std::string version;
        std::string core;
        bool status;
    };

public:
    std::string token;

    ServerHandler() {}

    ServerList getServers();
};

#endif // SERVERHANDLER_H
