#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QStackedLayout>
#include <QTimer>

#include "login/login.h"
#include "dashboard/dashboard.h"
#include "dashboard/mods.h"

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
    void updateToken();

private slots:
    // - - NET - -
    void createLoginHandler();
    void createServerHandler();

    // - - CONNECTS - -
    void startSetup();
    void setupNet();
    void setupLayout();
    void setupConnects();
    void loginPageConnects();
    void dashboardPageConnects();
    void modsPageConnects();

    // - - UI - -
    void changeForm(int formId);
    void reInitializePopUps();
    void showLoadScreen(QWidget* caller);
    void hideLoadScreen(QWidget* caller);
    void initDashboard(QWidget* caller, QString username, int rank);
    void infobarDisplay(QWidget* caller, std::string message, bool isFailure);

private:
    // - - NET - -
    LoginHandler* netLoginHandler;
    ServerHandler* netServerHandler;

    // - - UI - -
    QStackedLayout* layout;
    Login* login;
    Dashboard* dashboard;
    LoadingScreen* loadScreen;
    Mods* mods;
    InfoBar* infobar;
};
#endif // MAINWINDOW_H
