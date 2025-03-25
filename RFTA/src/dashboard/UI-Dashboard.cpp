#include "../../header/dashboard/dashboard.h"
#include "ui_dashboard.h"
#include "../../header/dashboard/UI-DashboardStyle.h"

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

void Dashboard::initButtonUI(QString username, int privileges, ServerHandler::Server server) {
    if (server.id <= 0) {
        qDebug() << "Invalid server";
        return;
    }

    bool isServerActive = server.status;
    QString consoleTemplate;
    if (privileges >= 4) {
        consoleTemplate = username + "@" + QString::fromStdString(server.name) + ":~# ";
    } else {
        consoleTemplate = username + "@" + QString::fromStdString(server.name) + ":~$ ";
    }
    ui->ConsoleUsername->setText(consoleTemplate);

    ui->StartButton->setEnabled(false);
    ui->StopButton->setEnabled(false);
    ui->StartButton->setStyleSheet(inactiveStartButtonStyle);
    ui->StopButton->setStyleSheet(inactiveStopButtonStyle);

    disconnect(ui->StartButton, &QPushButton::clicked, this, nullptr);
    disconnect(ui->StopButton, &QPushButton::clicked, this, nullptr);
    disconnect(ui->EditMPButton, &QPushButton::clicked, this, nullptr);
    disconnect(ui->EditServerButton, &QPushButton::clicked, this, nullptr);

    connect(ui->StartButton, &QPushButton::clicked, this, [this, server]() {
        startButtonHandler(server.id);
    });

    connect(ui->StopButton, &QPushButton::clicked, this, [this, server]() {
        stopButtonHandler(server.id);
    });

    connect(ui->EditMPButton, &QPushButton::clicked, this, [this, server]() {
        editMPButtonHandler(server.id);
    });

    connect(ui->EditServerButton, &QPushButton::clicked, this, [this, server]() {
        editServerButtonHandler(server.id);
    });

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
            // ui->EditServerButton->setEnabled(true);
            // ui->EditServerButton->setStyleSheet(activeEditButtonStyle);

            break;
        }
    }
}

void Dashboard::startButtonHandler(int serverId) {
    disableStartButton();
    enableStopButton();
}

void Dashboard::stopButtonHandler(int serverId) {
    disableStopButton();
    enableStartButton();
}

void Dashboard::editMPButtonHandler(int serverId) {
    emit S_ShowLoadingScreen(this);
    QTimer::singleShot(400, this, [this, serverId]() {
        emit S_EditMPSendData(serverId);
    });
}

void Dashboard::editMPAnswerHandler(std::string message, bool isFailure) {
    if (isFailure) {
        emit S_HideLoadingScreen(this);
        emit S_Infobar(this, message, true);
    } else {
        emit S_HideLoadingScreen(this);
        emit S_ChangeForm(2);
    }
}

void Dashboard::editServerButtonHandler(int serverId) {

}
