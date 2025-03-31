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

    LoginHandler() : cl("https://rfta.rotatick.ru") {
        cl.set_connection_timeout(0, 500000);
        cl.set_default_headers({{"Host", "rfta.rotatick.ru"}});
    }

    void loadData(QString usernameEntry, QString passwordEntry);
    Result sendRequest();
    bool checkServerStatus();
    void cacheToken(std::string token);
};

#endif // LOGINHANDLER_H
