#include "../header/login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}

void Login::tryLogin() {
    emit S_ShowLoadingScreen(this);
    // TODO: put api request here
    QTimer::singleShot(2000, this, [this]() {
        S_HideLoadingScreen(this);
        QString username = ui->UsernameInput->text();
        emit S_InitDashboard(username, 4, true);
    });
}

void Login::on_LoginButton_clicked() {
    tryLogin();
}


void Login::on_PasswordInput_returnPressed() {
    tryLogin();
}

