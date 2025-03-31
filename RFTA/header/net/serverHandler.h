#ifndef SERVERHANDLER_H
#define SERVERHANDLER_H

#define CPPHTTPLIB_OPENSSL_SUPPORT
#include <QObject>
#include <QFile>
#include <QFileInfo>

// QNetwork
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QHttpMultiPart>
#include <QSslConfiguration>
#include <QSslSocket>

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

    void loadMods(QUrl url, QString filePath, QString modType);

signals:
    void uploadFinished(bool isFinished);
    void uploadProgress(int progress);

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

    ServerHandler() : cl("https://rfta.rotatick.ru") {
        cl.set_connection_timeout(0, 500000);
        cl.set_default_headers({{"Host", "rfta.rotatick.ru"}});
    }

    bool checkToken();

    Result getServer(int serverId);

    Result getServers();

    Result executeCommand(int serverId, std::string command);

    Result restartServer(int serverId);

    Result getModPack(int serverId);

    Result loadJar(int serverId, QString filePath);

    Result loadZip(int serverId, QString filePath);

    Result deleteMod(int serverId, std::string modName);
};

#endif // SERVERHANDLER_H
