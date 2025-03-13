#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QTimer>
#include "../misc/clickQLabel.h"

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

signals:
    void S_InitDashboard(QString username, int rank, bool isServerActive);

    void S_ShowLoadingScreen(QWidget* caller);

    void S_HideLoadingScreen(QWidget* caller);

private slots:
    void tryLogin();

    void on_LoginButton_clicked();

    void on_PasswordInput_returnPressed();

    void togglePasswordVisibility();

private:
    Ui::Login *ui;
    bool isPasswordVisible = false;
    ClickQLabel* showPassword;
};

#endif // LOGIN_H
