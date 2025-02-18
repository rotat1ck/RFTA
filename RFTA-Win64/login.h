#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>

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
    void SUserData(QString username, int rank);

private slots:
    void tryLogin();

    void on_LoginButton_clicked();

    void on_PasswordInput_returnPressed();

private:
    Ui::Login *ui;

};

#endif // LOGIN_H
