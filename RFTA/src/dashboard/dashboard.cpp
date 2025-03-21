#include "../../header/dashboard/dashboard.h"
#include "ui_dashboard.h"

Dashboard::Dashboard(QWidget *parent, LoginHandler* loginHandlerEntry,
ServerHandler* serverHandlerEntry) : QWidget(parent),
    ui(new Ui::Dashboard), loginHandler(loginHandlerEntry), serverHandler(serverHandlerEntry)
{
    ui->setupUi(this);
}

Dashboard::~Dashboard()
{
    delete ui;
}

void Dashboard::initSequence(QString username, int rank) {
    QString privileges = QString::number(rank);
    ui->NameBar->setText(username);
    ui->Privileges->setText("#" + privileges);

    Dashboard::initBranches(username, rank);
    Dashboard::initButtonUI(rank);
}
