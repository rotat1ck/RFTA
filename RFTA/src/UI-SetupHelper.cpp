#include "../header/mainwindow.h"

void MainWindow::setupLayout() {
    login = new Login(this, netLoginHandler);
    dashboard = new Dashboard(this, netLoginHandler, netServerHandler);
    mods = new Mods(this);

    layout = new QStackedLayout;
    layout->addWidget(login);
    layout->addWidget(dashboard);
    layout->addWidget(mods);
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
    // Show loading screen
    connect(login, &Login::S_ShowLoadingScreen, this, &MainWindow::showLoadScreen);
    connect(login, &Login::S_HideLoadingScreen, this, &MainWindow::hideLoadScreen);

    // Infobar connects
    connect(login, &Login::S_Infobar, this, &MainWindow::infobarDisplay);

    // Login successful, redirect to dashboard
    connect(login, &Login::S_InitDashboard, this, &MainWindow::initDashboard);
}

void MainWindow::dashboardPageConnects() {
    // Change form
    connect(dashboard, &Dashboard::S_ChangeForm, this, &MainWindow::changeForm);
    connect(dashboard, &Dashboard::S_Infobar, this, &MainWindow::infobarDisplay);
}
