#include "../../header/login/login.h"
#include "../../header/net/loginHandler.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    ui->PasswordInput->setEchoMode(QLineEdit::Password);
    showPassword = new ClickQLabel(ui->centralwidget);
    showPassword->setText("Show password");
    showPassword->setGeometry(175, 300, 130, 20);

    connect(showPassword, &ClickQLabel::clicked, this, &Login::togglePasswordVisibility);
}

Login::~Login()
{
    delete ui;
}

void Login::tryLogin() {
    emit S_ShowLoadingScreen(this);
    QTimer::singleShot(400, this, [this]() {
        QString username = ui->UsernameInput->text();
        QString password = ui->PasswordInput->text();
        LoginHandler handler(username, password);
        auto result = handler.sendRequest();
        // emit S_InitDashboard(username, 4, true);

    });
}

void Login::on_LoginButton_clicked() {
    tryLogin();
}


void Login::on_PasswordInput_returnPressed() {
    tryLogin();
}

void Login::togglePasswordVisibility() {
    isPasswordVisible = !isPasswordVisible;
        if (isPasswordVisible) {
            ui->PasswordInput->setEchoMode(QLineEdit::Normal);
            showPassword->setText("Hide password");
        } else {
            ui->PasswordInput->setEchoMode(QLineEdit::Password);
            showPassword->setText("Show password");
        }
}
