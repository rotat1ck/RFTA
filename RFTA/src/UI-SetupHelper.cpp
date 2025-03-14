#include "../header/mainwindow.h"

void MainWindow::setupLayout() {
    login = new Login(this);
    dashboard = new Dashboard(this);

    layout = new QStackedLayout;
    layout->addWidget(login);
    layout->addWidget(dashboard);
    layout->setCurrentWidget(login);

    loadScreen = new LoadingScreen(this);
    infobar = new InfoBar(this);
    loadScreen->hide();
    infobar->hide();
}

void MainWindow::setupConnects() {
    loginPageConnects();
    dashboardPageConnects();
}

void MainWindow::loginPageConnects() {
    // Receive handler
    connect(login, &Login::S_CreateNetLoginHandler, this, &MainWindow::receiveNetLoginHandler);

    // Show loading screen
    connect(login, &Login::S_ShowLoadingScreen, this, &MainWindow::showLoadScreen);
    connect(login, &Login::S_HideLoadingScreen, this, &MainWindow::hideLoadScreen);

    // Infobar connects
    connect(login, &Login::S_Infobar, this, &MainWindow::infobarDisplay);

    // Login successful, redirect to dashboard
    connect(login, &Login::S_InitDashboard, dashboard, &Dashboard::receiveUserData);
    connect(login, &Login::S_ShowDashboard, this, &MainWindow::showDashboard);
}

void MainWindow::dashboardPageConnects() {
    // Receive handler
    connect(dashboard, &Dashboard::S_CreateNetServerHandler, this, &MainWindow::receiveNetServerHandler);

    // Change form
    connect(dashboard, &Dashboard::S_ChangeForm, this, &MainWindow::changeForm);
}
