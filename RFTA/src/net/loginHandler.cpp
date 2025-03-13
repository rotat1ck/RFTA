#include "../../header/net/loginHandler.h"

#include <iostream>

LoginHandler::LoginHandler(QString usernameEntry, QString passwordEntry) {
    username = "username=" + usernameEntry.toUtf8().toStdString();
    password = "pass=" + toHash::hash(passwordEntry.toUtf8().toStdString());
}

LoginHandler::Result LoginHandler::sendRequest() {
    httplib::Client cl("https://77.37.246.6:7777");
    cl.enable_server_certificate_verification(false);
    std::string endpoint = "api/users/login?" + username + "&" + password;
    auto res = cl.Get(endpoint);
    std::cout << res->body << std::endl;
    if (res->status != 200) {
        return {res->status, res->body, true};
    } else {
        return {res->status, res->body, false};
    }
}

void LoginHandler::cacheToken() {

}
