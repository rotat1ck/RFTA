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


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void setupLayout();
    void setupConnects();
    void loginPageConnects();
    void dashboardPageConnects();

    void changeForm(int formId);

    void reInitializePopUps();

    void showLoadScreen(QWidget* caller);

    void hideLoadScreen(QWidget* caller);

    void showDashboard(QWidget *caller);

    void infobarDisplay(QWidget* caller, std::string message, bool isFailure);

private:
    Login* login;
    Dashboard* dashboard;
    LoadingScreen* loadScreen;
    QStackedLayout* layout;
    InfoBar* infobar;
};
#endif // MAINWINDOW_H
