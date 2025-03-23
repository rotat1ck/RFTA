#include "../../header/dashboard/dashboard.h"
#include "ui_dashboard.h"

QString activeServerButtonStyle =
    "background: rgba(155, 155, 155, 1);"
    "border-radius: 15px;"
    "font-family: 'Inter SemiBold';"
    "font-size: 18px;"
    "line-height: 22px;"
    "color: rgba(0, 0, 0, 1);"
;

QString inactiveServerButtonStyle =
    "background: rgba(124, 124, 124, 76);"
    "border-radius: 15px;"
    "font-family: 'Inter SemiBold';"
    "font-size: 18px;"
    "line-height: 22px;"
    "color: rgba(0, 0, 0, 76);"
;

void Dashboard::initBranches(QString username, int rank) {
    getServers();

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
            }

            button->setStyleSheet(activeServerButtonStyle);
            initButtonUI(username, rank, server);
            std::cout << "Button for server " << server.id << " clicked." << std::endl;
        });

        serversLayout->addWidget(button);
    }

    if (!serverHandler->servers.empty()) {
        initButtonUI(username, rank, serverHandler->servers[0]);
    }

}

void Dashboard::getServers() {
    serverHandler->servers.clear();
    try {
        if (loginHandler->checkServerStatus()) {
            auto result = serverHandler->getServers(loginHandler->token);
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
        } else {
            emit S_Infobar(this, "Connection failed", true);
        }
    } catch (json::parse_error& ex) {
        emit S_Infobar(this, "Unexpected error", true);
    } catch (std::exception ex) {
        emit S_Infobar(this, "Unexpected error", true);
    }
}
