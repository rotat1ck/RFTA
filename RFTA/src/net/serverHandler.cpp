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

ServerHandler::Result ServerHandler::getServer(int serverId) {
    cl.set_default_headers({{"Authorization", "Bearer " + token}});

    std::string endpoint = "api/servers/" + std::to_string(serverId);
    if (auto res = cl.Get(endpoint)) {
        return {res->status, res->body};
    } else {
        return {0, ""};
    }
}

ServerHandler::Result ServerHandler::getModPack(int serverId) {
    cl.set_default_headers({{"Authorization", "Bearer " + token}});

    std::string endpoint = "api/servers/getmp/" + std::to_string(serverId);
    if (auto res = cl.Get(endpoint)) {
        return {res->status, res->body};
    } else {
        return {0, ""};
    }
}

ServerHandler::Result ServerHandler::loadJar(int serverId, QString filePath) {
    loadMods(QUrl("https://77.37.246.6:7777/api/controller/loadjar/" + QString::number(serverId)), filePath, "mod");
    return {0, ""};
}

ServerHandler::Result ServerHandler::loadZip(int serverId, QString filePath) {
    loadMods(QUrl("https://77.37.246.6:7777/api/controller/loadzip/" + QString::number(serverId)), filePath, "zip");
    return {0, ""};
}

void ServerHandler::loadMods(QUrl url, QString filePath, QString modType) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Failed to open file:" << file.errorString();
        emit uploadFinished(false);
        return;
    }

    qint64 totalBytes = file.size();

    QNetworkAccessManager* manager = new QNetworkAccessManager(this);
    QNetworkRequest request(url);
    request.setRawHeader("Authorization", ("Bearer " + QString::fromStdString(token)).toUtf8());
    request.setTransferTimeout(3000);

    QHttpMultiPart* multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
    QHttpPart filePart;
    filePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/octet-stream"));
    filePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"" + modType + "\"; filename=\"" + QFileInfo(file).fileName() + "\""));
    filePart.setBody(file.readAll());
    multiPart->append(filePart);

    try {
        QNetworkReply* reply = manager->post(request, multiPart);

        if (!reply) {
            emit uploadFinished(false);
            return;
        }

        connect(reply, &QNetworkReply::sslErrors, this, [reply](const QList<QSslError>& errors) {
            reply->ignoreSslErrors();
        });

        connect(reply, &QNetworkReply::finished, this, [this, manager, totalBytes, reply]() {
            if (reply->error() == QNetworkReply::NoError) {
                emit uploadFinished(true);
            } else {
                qDebug() << "Upload error:" << reply->errorString(); // Log the error
                emit uploadFinished(false);
            }
            manager->deleteLater();
            reply->deleteLater();
        });

        connect(reply, &QNetworkReply::uploadProgress, this, [this, totalBytes](qint64 bytesSent, qint64 bytesTotal) {
            int progress = static_cast<int>((bytesSent * 100) / totalBytes);
            emit uploadProgress(progress);
        });
    } catch (std::exception ex) {
        emit uploadFinished(false);
    }

    return;
}
