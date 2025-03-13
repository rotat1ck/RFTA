#ifndef LOGINHANDLER_H
#define LOGINHANDLER_H

#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "../utils/httplib.h"
#include "../misc/hasher.h"
#include <QString>

class LoginHandler {
private:
    std::string username;

    std::string password;

    std::string token;

    struct Result {
        int status;
        std::string message;
        bool isFailure;
    };

public:
    LoginHandler(QString usernameEntry, QString passwordEntry);

    Result sendRequest();

    void cacheToken();
};

#endif // LOGINHANDLER_H
