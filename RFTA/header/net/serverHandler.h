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
    struct Result {
        int status;
        std::string message;
    };

public:
    std::string token;

    ServerHandler() {}

    Result getServers(std::string tokenEntry);
};

#endif // SERVERHANDLER_H
