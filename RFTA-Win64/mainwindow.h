#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QStackedLayout>

#include "login.h"
#include "dashboard.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void changeForm(int formId);

    void showDashboard(QString username);


private:
    Login* login;
    Dashboard* dashboard;
    QStackedLayout* layout;
};
#endif // MAINWINDOW_H
