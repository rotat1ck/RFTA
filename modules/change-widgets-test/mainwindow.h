#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QStackedLayout>

#include "loginwidget.h"
#include "dashboardwidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    LoginWidget* login;
    DashboardWidget* dashboard;
    QStackedLayout* layout;

private slots:
    void changeForm(int formId);

};



#endif // MAINWINDOW_H
