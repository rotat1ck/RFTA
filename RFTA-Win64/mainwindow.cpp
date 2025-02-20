#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    login = new Login(this);
    dashboard = new Dashboard(this);

    layout = new QStackedLayout;
    layout->addWidget(login);
    layout->addWidget(dashboard);

    layout->setCurrentWidget(login);
    loadScreen = new LoadingScreen(this);
    loadScreen->hide();

    connect(login, &Login::S_InitDashboard, dashboard, &Dashboard::receiveUserData);
    connect(login, &Login::S_InitDashboard, this, &MainWindow::showDashboard);

    connect(dashboard, &Dashboard::SChangeForm, this, &MainWindow::changeForm);
}

MainWindow::~MainWindow()
{
    delete login;
    delete dashboard;
    delete loadScreen;
    delete layout;
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
    loadScreen->show();
}

void MainWindow::showLoadScreen() {
    loadScreen->show();
    login->setEnabled(false);
    QTimer::singleShot(3000, this, [this]() {
            loadScreen->hide();
            login->setEnabled(true);
    });
}

void MainWindow::hideLoadScreen() {

}
