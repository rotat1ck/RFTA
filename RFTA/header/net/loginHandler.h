#ifndef LOGINHANDLER_H
#define LOGINHANDLER_H

#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "../utils/httplib.h"
#include "../misc/hasher.h"
#include <QString>
#include <QObject>

class LoginHandler : public QObject {
    Q_OBJECT
private:
    httplib::Client cl;

    std::string username;

    std::string password;

    struct Result {
        int status;
        std::string message;
        bool isFailure;
    };
signals:
    void S_CacheToken(std::string token);

public:
    std::string token;

    LoginHandler() : cl("https://77.37.246.6:7777") {
        cl.enable_server_certificate_verification(false);
        cl.set_connection_timeout(0, 500000);
    }

    void loadData(QString usernameEntry, QString passwordEntry);
    Result sendRequest();
    bool checkServerStatus();
    void cacheToken(std::string token);
};

#endif // LOGINHANDLER_H
