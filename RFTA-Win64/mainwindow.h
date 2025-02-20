#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QStackedLayout>
#include <QTimer>

#include "login.h"
#include "dashboard.h"
#include "loadingscreen.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void changeForm(int formId);

    void showDashboard(QString username);

    void showLoadScreen();

    void hideLoadScreen();

private:
    Login* login;
    Dashboard* dashboard;
    LoadingScreen* loadScreen;
    QStackedLayout* layout;
};
#endif // MAINWINDOW_H
