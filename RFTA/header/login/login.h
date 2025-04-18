#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QTimer>
#include "../net/loginHandler.h"
#include "../misc/clickQLabel.h"
#include "../utils/json.hpp"
using json = nlohmann::json;

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr, LoginHandler* handlerEntry = nullptr);
    ~Login();

signals:
    // - - UI - -
    void S_InitDashboard(QWidget* caller, QString username, int rank);
    void S_ShowLoadingScreen(QWidget* caller);
    void S_HideLoadingScreen(QWidget* caller);
    void S_Infobar(QWidget* caller, std::string, bool isFailure);

private slots:
    void tryLogin();

    void on_LoginButton_clicked();

    void on_PasswordInput_returnPressed();

    void togglePasswordVisibility();

private:
    Ui::Login *ui;
    bool isPasswordVisible = false;
    ClickQLabel* showPassword;
    LoginHandler* handler;
};

#endif // LOGIN_H
