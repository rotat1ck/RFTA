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

void MainWindow::updateToken() {
    try {
        if (netLoginHandler->checkServerStatus()) {
            auto result = netLoginHandler->sendRequest();
            json response = json::parse(result.message);
            if (result.status != 200) {
                return;
            } else {
                netServerHandler->token = response["token"];
                netLoginHandler->token = response["token"];
                return;
            }
        }
    } catch (json::parse_error& ex) {
        return;
    } catch (std::exception ex) {
        return;
    }
}
