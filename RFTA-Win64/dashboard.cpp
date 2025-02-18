#include "dashboard.h"
#include "ui_dashboard.h"

#include "mainwindow.h"

Dashboard::Dashboard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Dashboard)
{
    ui->setupUi(this);
}

Dashboard::~Dashboard()
{
    delete ui;
}

void Dashboard::receiveUserData(QString username, int rank) {
    QString privileges = QString::number(rank);
    ui->NameBar->setText(username);
    ui->Privileges->setText("#" + privileges);
}

void Dashboard::on_ExitButton1_clicked() {
    emit SChangeForm(0);
}


void Dashboard::on_ExitButton2_clicked() {
    emit SChangeForm(0);
}

