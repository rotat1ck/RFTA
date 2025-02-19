#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QStackedLayout>
#include <QTimer>
#include "login.h"
#include "loading.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Login* login;
    Loading* loadScreen;
    QStackedLayout* layout;

};
#endif // MAINWINDOW_H
