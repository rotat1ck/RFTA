#include "../header/mainwindow.h"

void MainWindow::setupNet() {
    createLoginHandler();
    createServerHandler();
}

void MainWindow::createLoginHandler() {
    netLoginHandler = new LoginHandler();
}

void MainWindow::createServerHandler() {
    netServerHandler = new ServerHandler();
}
