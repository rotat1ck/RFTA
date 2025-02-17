#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    login = new LoginWidget(this);
    dashboard = new DashboardWidget(this);

    layout = new QStackedLayout;
    layout->addWidget(login);
    layout->addWidget(dashboard);

    layout->setCurrentWidget(login);

    connect(login, &LoginWidget::SChangeForm, this, &MainWindow::changeForm);
    connect(dashboard, &DashboardWidget::SChangeForm, this, &MainWindow::changeForm);
}


MainWindow::~MainWindow()
{
    delete login;
    delete dashboard;
    delete layout;
}

void MainWindow::changeForm(int formId) {
    switch(formId) {
    case 0: {
        layout->setCurrentWidget(login);
        break;
    } case 1: {
        layout->setCurrentWidget(dashboard);
        break;
    }
    }
}
