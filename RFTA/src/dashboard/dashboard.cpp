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

// TODO: get a list of branches from API to fill the branch section
void Dashboard::initSequence(QString username, int rank) {
    QString privileges = QString::number(rank);
    ui->NameBar->setText(username);
    ui->Privileges->setText("#" + privileges);

    Dashboard::initButtonUI(rank, true);
    Dashboard::getServers(username, rank);
}
