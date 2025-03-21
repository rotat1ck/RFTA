#include "../../header/dashboard/dashboard.h"
#include "ui_dashboard.h"
#include "../../header/dashboard/UI-DashboardStyle.h"
#include "../../header/mainwindow.h"

void Dashboard::on_ExitButton1_clicked() {
    emit S_ChangeForm(0);
}

void Dashboard::on_ExitButton2_clicked() {
    emit S_ChangeForm(0);
}

void Dashboard::enableStartButton() {
    ui->StartButton->setEnabled(true);
    ui->StartButton->setStyleSheet(activeStartButtonStyle);
}

void Dashboard::disableStartButton() {
    ui->StartButton->setEnabled(false);
    ui->StartButton->setStyleSheet(inactiveStartButtonStyle);
}

void Dashboard::enableStopButton() {
    ui->StopButton->setEnabled(true);
    ui->StopButton->setStyleSheet(activeStopButtonStyle);
}

void Dashboard::disableStopButton() {
    ui->StopButton->setEnabled(false);
    ui->StopButton->setStyleSheet(inactiveStopButtonStyle);
}

void Dashboard::initButtonUI(int privileges) {
    bool isServerActive = serverHandler->servers[0].status;
    switch(privileges) {
        case 2: {
            if (!isServerActive) {
                enableStartButton();
            }

            break;
        } case 3: {
            if (isServerActive) {
                enableStopButton();
            } else {
                enableStartButton();
            }

            ui->EditMPButton->setEnabled(true);
            ui->EditMPButton->setStyleSheet(activeEditButtonStyle);

            break;
        } case 4: {
            if (isServerActive) {
                enableStopButton();
            } else {
                enableStartButton();
            }

            ui->EditMPButton->setEnabled(true);
            ui->EditMPButton->setStyleSheet(activeEditButtonStyle);
            ui->EditServerButton->setEnabled(true);
            ui->EditServerButton->setStyleSheet(activeEditButtonStyle);

            break;
        } case 5: {
            if (isServerActive) {
                enableStopButton();
            } else {
                enableStartButton();
            }

            ui->EditMPButton->setEnabled(true);
            ui->EditMPButton->setStyleSheet(activeEditButtonStyle);
            ui->EditServerButton->setEnabled(true);
            ui->EditServerButton->setStyleSheet(activeEditButtonStyle);
        }
    }
}

void Dashboard::initBranches(QString username, int rank) {
    getServers();

    QString consoleTemplate;
    if (rank >= 4) {
        consoleTemplate = username + "@" + QString::fromStdString(serverHandler->servers[0].name) + ":~# ";
    } else {
        consoleTemplate = username + "@" + QString::fromStdString(serverHandler->servers[0].name) + ":~$ ";
    }
    ui->ConsoleUsername->setText(consoleTemplate);
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

void Dashboard::on_StartButton_clicked() {
    disableStartButton();
    enableStopButton();
}

void Dashboard::on_StopButton_clicked() {
    disableStopButton();
    enableStartButton();
}

void Dashboard::on_EditServerButton_clicked() {
    qDebug() << "Edit server";
}

void Dashboard::on_EditMPButton_clicked() {
    qDebug() << "Edit MP";
}
