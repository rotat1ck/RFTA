#include "../header/mainwindow.h"
#include <iostream>

void MainWindow::receiveNetLoginHandler(LoginHandler *loginHandler) {
    netLoginHandler = loginHandler;
    std::cout << "Received handler" << std::endl;
    connect(netLoginHandler, &LoginHandler::S_CacheToken, this, &MainWindow::receiveLoginToken);
}

void MainWindow::receiveNetServerHandler(ServerHandler *serverHandler) {
    netServerHandler = serverHandler;
}

void MainWindow::receiveLoginToken(std::string recToken) {
    token = recToken;
    std::cout << token << std::endl;
}

