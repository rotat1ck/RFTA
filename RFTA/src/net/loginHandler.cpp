#include "../../header/net/loginHandler.h"

void LoginHandler::loadData(QString usernameEntry, QString passwordEntry) {
    username = "username=" + usernameEntry.toUtf8().toStdString();
    password = "pass=" + toHash::hash(passwordEntry.toUtf8().toStdString());
}

bool LoginHandler::checkServerStatus() {
    std::string endpoint = "/api/users/healthcheck";

    if (cl.Get(endpoint)) {
        return true;
    } else {
        return false;
    }
}

LoginHandler::Result LoginHandler::sendRequest() {
    std::string endpoint = "/api/users/login?" + username + "&" + password;

    if (auto res = cl.Get(endpoint)) {
        if (res->status != 200) {
            return {res->status, res->body, true};
        } else {
            return {res->status, res->body, false};
        }
    } else {
        return {0, "", true};
    }
}
