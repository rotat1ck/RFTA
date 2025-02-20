#include "login.h"
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
    // put api request here
    emit S_ShowLoadingScreen(this);
    QTimer::singleShot(2000, this, [this]() {
        S_HideLoadingScreen(this);
        QString username = ui->UsernameInput->text();
        emit S_InitDashboard(username, 3, false);
    });


}

void Login::on_LoginButton_clicked() {
    tryLogin();
}


void Login::on_PasswordInput_returnPressed() {
    tryLogin();
}

