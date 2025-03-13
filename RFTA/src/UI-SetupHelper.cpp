#include "../header/mainwindow.h"

void MainWindow::setupLayout() {
    login = new Login(this);
    dashboard = new Dashboard(this);

    layout = new QStackedLayout;
    layout->addWidget(login);
    layout->addWidget(dashboard);

    layout->setCurrentWidget(login);
    loadScreen = new LoadingScreen(this);
    loadScreen->hide();
}

void MainWindow::setupConnects() {
    // Login page send request to API
    // Show loading screen
    connect(login, &Login::S_ShowLoadingScreen, this, &MainWindow::showLoadScreen);
    connect(login, &Login::S_HideLoadingScreen, this, &MainWindow::hideLoadScreen);

    // Login successful, redirect to dashboard
    connect(login, &Login::S_InitDashboard, dashboard, &Dashboard::receiveUserData);
    connect(login, &Login::S_InitDashboard, this, &MainWindow::showDashboard);

    // Widgets changhes (pages changes)
    connect(dashboard, &Dashboard::S_ChangeForm, this, &MainWindow::changeForm);
}
