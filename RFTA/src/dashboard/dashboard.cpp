#include "../../header/dashboard/dashboard.h"
#include "ui_dashboard.h"

#include "../../header/mainwindow.h"

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
void Dashboard::receiveUserData(QString username, int rank, bool isServerActive) {
    qDebug() << loginHandler->token;
    QString privileges = QString::number(rank);
    ui->NameBar->setText(username);
    ui->Privileges->setText("#" + privileges);
    QString consoleTemplate;
    if (rank >= 4) {
        // TODO: change Main with first branch from list
        consoleTemplate = username + "@" + "Main" + ":~# ";
    } else {
        // TODO: change Main with first branch from list
        consoleTemplate = username + "@" + "Main" + ":~$ ";
    }
    ui->ConsoleUsername->setText(consoleTemplate);

    initButtonUI(rank, isServerActive);
}
