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
    QString username = ui->UsernameInput->text();
    emit SUserData(username, 4);
}

void Login::on_LoginButton_clicked() {
    tryLogin();
}


void Login::on_PasswordInput_returnPressed() {
    tryLogin();
}

