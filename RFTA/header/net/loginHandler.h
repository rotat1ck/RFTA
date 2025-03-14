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

    LoginHandler() {}

    void loadData(QString usernameEntry, QString passwordEntry);
    Result sendRequest();
    void cacheToken(std::string token);
};

#endif // LOGINHANDLER_H
