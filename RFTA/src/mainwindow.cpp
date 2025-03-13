#include "../header/mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    login = new Login(this);
    dashboard = new Dashboard(this);

    layout = new QStackedLayout;
    layout->addWidget(login);
    layout->addWidget(dashboard);

    layout->setCurrentWidget(login);
    loadScreen = new LoadingScreen(this);
    loadScreen->hide();

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
            break;
        }
    }
    reInitializeLoadingScreen();
}

void MainWindow::showDashboard() {
    layout->setCurrentWidget(dashboard);
}

void MainWindow::reInitializeLoadingScreen() {
    delete loadScreen;
    loadScreen = new LoadingScreen(this);
    loadScreen->hide();
}

// TODO: add a blur effect to screen when called
void MainWindow::showLoadScreen(QWidget* caller) {
    loadScreen->show();
    caller->setEnabled(false);
}

void MainWindow::hideLoadScreen(QWidget* caller) {
    loadScreen->hide();
    caller->setEnabled(true);
}
