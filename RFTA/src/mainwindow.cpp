#include "../header/mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    startSetup();
}

void MainWindow::startSetup() {
    setupNet();
    setupLayout();
    setupConnects();
}

MainWindow::~MainWindow() {
    delete login;
    delete dashboard;
    delete mods;
    delete loadScreen;
    delete layout;
    delete infobar;
    delete netLoginHandler;
    delete netServerHandler;
}

void MainWindow::changeForm(int formId) {
    switch(formId) {
        case 0: {
            layout->setCurrentWidget(login);
            break;
        } case 1: {
            layout->setCurrentWidget(dashboard);
            break;
        } case 2: {
            layout->setCurrentWidget(mods);
            break;
        }
    }
    reInitializePopUps();
}

void MainWindow::reInitializePopUps() {
    delete loadScreen;
    delete infobar;
    loadScreen = new LoadingScreen(this);
    infobar = new InfoBar(this, "");
    loadScreen->hide();
    infobar->hide();
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

void MainWindow::initDashboard(QWidget* caller, QString username, int rank) {
    dashboard->initSequence(username, rank);
    changeForm(1);
    infobarDisplay(caller, "Successful login", false);
}

void MainWindow::infobarDisplay(QWidget *caller, std::string message, bool isFailure) {
    infobar->displayMessage(message, isFailure);
    infobar->show();
    QTimer::singleShot(2000, this, [this]() {
        infobar->hide();
    });
}
