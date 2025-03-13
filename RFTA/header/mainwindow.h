#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QStackedLayout>
#include <QTimer>

#include "login/login.h"
#include "dashboard/dashboard.h"
#include "loadScreen/loadingscreen.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void setupLayout();
    void setupConnects();

    void changeForm(int formId);

    void showDashboard();

    void reInitializeLoadingScreen();

    void showLoadScreen(QWidget* caller);

    void hideLoadScreen(QWidget* caller);

private:
    Login* login;
    Dashboard* dashboard;
    LoadingScreen* loadScreen;
    QStackedLayout* layout;
};
#endif // MAINWINDOW_H
