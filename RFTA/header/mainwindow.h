#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QStackedLayout>
#include <QTimer>

#include "login/login.h"
#include "dashboard/dashboard.h"
#include "loadScreen/loadingscreen.h"
#include "misc/infobar.h"
#include "net/loginHandler.h"
#include "net/serverHandler.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    std::string token;

private slots:
    // - - NET - -
    void receiveNetLoginHandler(LoginHandler* loginHandler);
    void receiveNetServerHandler(ServerHandler* serverHandler);
    void receiveLoginToken(std::string recToken);

    // - - CONNECTS - -
    void setupLayout();
    void setupConnects();
    void loginPageConnects();
    void dashboardPageConnects();

    // - - UI - -
    void changeForm(int formId);
    void reInitializePopUps();
    void showLoadScreen(QWidget* caller);
    void hideLoadScreen(QWidget* caller);
    void showDashboard(QWidget *caller);
    void infobarDisplay(QWidget* caller, std::string message, bool isFailure);

private:
    // - - NET - -
    LoginHandler* netLoginHandler;
    ServerHandler* netServerHandler;

    // - - UI - -
    Login* login;
    Dashboard* dashboard;
    LoadingScreen* loadScreen;
    QStackedLayout* layout;
    InfoBar* infobar;
};
#endif // MAINWINDOW_H
