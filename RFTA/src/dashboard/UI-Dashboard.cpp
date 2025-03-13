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

void Dashboard::initButtonUI(int privileges, bool isServerActive) {
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
        }
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
