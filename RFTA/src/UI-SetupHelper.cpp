#include "../header/mainwindow.h"

void MainWindow::setupLayout() {
    login = new Login(this, netLoginHandler);
    dashboard = new Dashboard(this, netLoginHandler, netServerHandler);
    mods = new Mods(this, netLoginHandler, netServerHandler);

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
    modsPageConnects();
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
    // Show loading screen
    connect(dashboard, &Dashboard::S_ShowLoadingScreen, this, &MainWindow::showLoadScreen);
    connect(dashboard, &Dashboard::S_HideLoadingScreen, this, &MainWindow::hideLoadScreen);

    // Change form
    connect(dashboard, &Dashboard::S_ChangeForm, this, &MainWindow::changeForm);
    connect(dashboard, &Dashboard::S_Infobar, this, &MainWindow::infobarDisplay);

    // EditMP
    connect(dashboard, &Dashboard::S_EditMPSendData, mods, &Mods::receiveServerId);
    connect(mods, &Mods::S_RequestResult, dashboard, &Dashboard::editMPAnswerHandler);

    // Update token
    connect(dashboard, &Dashboard::S_UpdateToken, this, &MainWindow::updateToken);
}

void MainWindow::modsPageConnects() {
    // Show loading screen
    connect(mods, &Mods::S_ShowLoadingScreen, this, &MainWindow::showLoadScreen);
    connect(mods, &Mods::S_HideLoadingScreen, this, &MainWindow::hideLoadScreen);

    // Change form
    connect(mods, &Mods::S_ChangeForm, this, &MainWindow::changeForm);
    connect(mods, &Mods::S_Infobar, this, &MainWindow::infobarDisplay);

    // Update token
    connect(mods, &Mods::S_UpdateToken, this, &MainWindow::updateToken);
}
