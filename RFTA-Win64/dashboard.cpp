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

void Dashboard::receiveUserData(QString username, int rank, bool isServerActive) {
    QString privileges = QString::number(rank);
    ui->NameBar->setText(username);
    ui->Privileges->setText("#" + privileges);
    initButtonUI(rank, isServerActive);
}

