#include "../../header/login/login.h"
#include "ui_login.h"

Login::Login(QWidget *parent, LoginHandler* handlerEntry) : QWidget(parent),
    ui(new Ui::Login), handler(handlerEntry)
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
        handler->loadData(username, password);
        try {
            if (handler->checkServerStatus()) {
                auto result = handler->sendRequest();
                json response = json::parse(result.message);
                if (result.status != 200) {
                    emit S_Infobar(this, response["error"], true);
                } else {
                    int role = response["role"];
                    handler->token = response["token"];
                    // change true to request of the branches
                    emit S_InitDashboard(username, role);
                    emit S_ShowDashboard(this);
                }
            } else {
                emit S_Infobar(this, "Connection failed", true);
            }
        } catch (json::parse_error& ex) {
            emit S_Infobar(this, "Unexpected error", true);
        } catch (std::exception ex) {
            emit S_Infobar(this, "Unexpected error", true);
        }

        emit S_HideLoadingScreen(this);
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
