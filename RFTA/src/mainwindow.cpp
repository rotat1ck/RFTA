#include "../header/mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setupLayout();
    setupConnects();
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
