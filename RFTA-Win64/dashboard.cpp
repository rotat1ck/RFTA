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

void Dashboard::on_pushButton_clicked()
{
    emit SChangeForm(0);
}

void Dashboard::receiveUserData(QString username, int rank) {
    QString priviliges = QString::number(rank);
    ui->label->setText(username + priviliges);
}
