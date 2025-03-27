#include "../../header/dashboard/dashboard.h"
#include "ui_dashboard.h"

Dashboard::Dashboard(QWidget *parent, LoginHandler* loginHandlerEntry, ServerHandler* serverHandlerEntry)
    : QWidget(parent), ui(new Ui::Dashboard), loginHandler(loginHandlerEntry), serverHandler(serverHandlerEntry)
{
    ui->setupUi(this);
    serversLayout = new QVBoxLayout(ui->Branches);
    serversLayout->setAlignment(Qt::AlignTop);
    serversLayout->setContentsMargins(5, 10, 5, 0);
    serversLayout->setSpacing(10);


}

Dashboard::~Dashboard() {
    delete ui;
    delete serversLayout;
}

void Dashboard::initSequence(QString username, int rank) {
    QString privileges = QString::number(rank);
    ui->NameBar->setText(username);
    ui->Privileges->setText("#" + privileges);

    Dashboard::initBranches(username, rank);
}
