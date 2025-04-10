#include "../../header/dashboard/dashboard.h"
#include "ui_dashboard.h"

void Dashboard::initBranches(QString username, int rank) {
    getServers();
    initServersConsoleLayout();
    setConsoleLayout(serversConsoleLayout.begin().key());

    if (serversLayout) {
        QLayoutItem* item;
        while ((item = serversLayout->takeAt(0))) {
            delete item->widget();
            delete item;
        }
        delete serversLayout;
    }

    serversLayout = new QVBoxLayout(ui->Branches);
    serversLayout->setAlignment(Qt::AlignTop);
    serversLayout->setContentsMargins(5, 10, 5, 0);
    serversLayout->setSpacing(10);

    for (auto server : serverHandler->servers) {
        QPushButton* button = new QPushButton(QString::fromStdString(server.name));
        button->setObjectName(QString::fromStdString("server_" + server.name + "_button"));
        button->setCursor(Qt::PointingHandCursor);
        button->setFixedSize(120, 35);

        if (server.id == 1) {
            button->setStyleSheet(activeServerButtonStyle);
        } else {
            button->setStyleSheet(inactiveServerButtonStyle);
        }

        connect(button, &QPushButton::clicked, this, [this, button, username, rank, server]() {
            for (int i = 0; i < serversLayout->count(); ++i) {
                QLayoutItem* item = serversLayout->itemAt(i);
                QPushButton* btn = qobject_cast<QPushButton*>(item->widget());
                btn->setStyleSheet(inactiveServerButtonStyle);
                this->setConsoleLayout(server.id);
            }

            button->setStyleSheet(activeServerButtonStyle);
            initButtonUI(username, rank, server);
        });

        serversLayout->addWidget(button);
    }

    if (!serverHandler->servers.empty()) {
        initButtonUI(username, rank, serverHandler->servers[0]);
    }

}

void Dashboard::getServers() {
    serverHandler->servers.clear();
    serverHandler->token = loginHandler->token;
    try {
        if (serverHandler->checkToken()) {
            uptadeServerList();
        } else if (loginHandler->checkServerStatus()) {
            int tries = 0;
            bool isSuccess = false;
            while (tries < 3) {
                emit S_UpdateToken();
                tries++;
                if (serverHandler->checkToken()) {
                    isSuccess = true;
                    break;
                }
            }
            if (isSuccess) {
                uptadeServerList();
            } else {
                emit S_Infobar(this, "Failed to update token", true);
            }
        } else {
            emit S_Infobar(this, "Connection failed", true);
        }
    } catch (json::parse_error& ex) {
        emit S_Infobar(this, "Unexpected error", true);
    } catch (std::exception& ex) {
        emit S_Infobar(this, "Unexpected error", true);
    }
}

void Dashboard::uptadeServerList() {
    auto result = serverHandler->getServers();
    json response = json::parse(result.message);
    if (result.status != 200) {
        emit S_Infobar(this, response["error"], true);
    } else {
        for (auto server : response["servers"]) {
            ServerHandler::Server info;
            info.id = server["id"];
            info.name = server["name"];
            info.core = server.contains("core") && !server["core"].is_null() ? server["core"].get<std::string>() : "";
            info.version = server.contains("version") && !server["version"].is_null() ? server["version"].get<std::string>() : "";
            info.status = server["status"].get<bool>();

            serverHandler->servers.push_back(info);
        }
    }
}

void Dashboard::initServersConsoleLayout() {
    serversConsoleLayout.clear();
    auto servers = serverHandler->servers;

    for (auto server : servers) {
        QWidget* container = new QWidget();

        QVBoxLayout* serverOutputLayout = new QVBoxLayout(container);
        serverOutputLayout->setAlignment(Qt::AlignBottom);
        container->setLayout(serverOutputLayout);

        int index = ConsoleScrollLayouts->addWidget(container);
        serversConsoleLayout.insert(server.id, index);
    }
}

int Dashboard::sendExecuteCommand(int serverId, QString command) {
    serverHandler->token = loginHandler->token;
    try {
        if (serverHandler->checkToken()) {
            auto res = serverHandler->executeCommand(serverId, command.toUtf8().toStdString());
            json response = json::parse(res.message);
            addTextConsoleLayout("Response: " + QString::fromStdString(response["message"]));
            return res.status;
        } else if (loginHandler->checkServerStatus()) {
            int tries = 0;
            bool isSuccess = false;
            while (tries < 3) {
                emit S_UpdateToken();
                tries++;
                if (serverHandler->checkToken()) {
                    isSuccess = true;
                    break;
                }
            }
            if (isSuccess) {
                auto res = serverHandler->executeCommand(serverId, command.toUtf8().toStdString());
                json response = json::parse(res.message);
                addTextConsoleLayout("Response: " + QString::fromStdString(response["message"]));
                return res.status;
            } else {
                emit S_Infobar(this, "Failed to update token", true);
            }
        } else {
            emit S_Infobar(this, "Connection failed", true);
        }
    } catch (json::parse_error& ex) {
        emit S_Infobar(this, "Unexpected error", true);
    } catch (std::exception& ex) {
        emit S_Infobar(this, "Unexpected error", true);
    }
    return 0;
}
