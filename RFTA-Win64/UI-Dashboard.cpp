#include "dashboard.h"
#include "ui_dashboard.h"
#include "UI-DashboardStyle.h"
#include "mainwindow.h"

void Dashboard::on_ExitButton1_clicked() {
    emit SChangeForm(0);
}

void Dashboard::on_ExitButton2_clicked() {
    emit SChangeForm(0);
}

void Dashboard::initButtonUI(int privileges, bool isServerActive) {
    if (privileges >= 2 && !isServerActive) {
        ui->StartButton->setEnabled(true);
        ui->StartButton->setStyleSheet(activeStartButtonStyle);
    } if (privileges >= 3 && isServerActive) {
        ui->StopButton->setEnabled(true);
        ui->StopButton->setStyleSheet(activeStopButtonStyle);
    } if (privileges >= 4) {
        ui->EditServerButton->setEnabled(true);
        ui->EditServerButton->setStyleSheet(activeEditServerButtonStyle);
    }
}

void Dashboard::on_StartButton_clicked() {
    ui->StartButton->setEnabled(false);
    ui->StartButton->setStyleSheet(inactiveStartButtonStyle);
    ui->StopButton->setEnabled(true);
    ui->StopButton->setStyleSheet(activeStopButtonStyle);
}

void Dashboard::on_StopButton_clicked() {
    ui->StopButton->setEnabled(false);
    ui->StopButton->setStyleSheet(inactiveStopButtonStyle);
    ui->StartButton->setEnabled(true);
    ui->StartButton->setStyleSheet(activeStartButtonStyle);
}

void Dashboard::on_EditServerButton_clicked() {
    qDebug() << "Edit server";
}
