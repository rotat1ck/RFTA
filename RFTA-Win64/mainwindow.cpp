#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    login = new Login(this);
    dashboard = new Dashboard(this);

    layout = new QStackedLayout;
    layout->addWidget(login);
    layout->addWidget(dashboard);

    layout->setCurrentWidget(login);

    connect(login, &Login::SUserData, dashboard, &Dashboard::receiveUserData);
    connect(login, &Login::SUserData, this, &MainWindow::showDashboard);

    connect(dashboard, &Dashboard::SChangeForm, this, &MainWindow::changeForm);
}

MainWindow::~MainWindow()
{
    delete login;
    delete dashboard;
    delete layout;
}

void MainWindow::tryLogin() {
    qDebug() << "LoginFunc";
}

void MainWindow::changeForm(int formId) {
    switch(formId) {
    case 0: {
        layout->setCurrentWidget(login);
    }
    }
}

void MainWindow::showDashboard(QString username) {
    layout->setCurrentWidget(dashboard);
}

