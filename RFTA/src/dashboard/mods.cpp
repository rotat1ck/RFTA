#include "../../header/dashboard/mods.h"
#include "ui_mods.h"

Mods::Mods(QWidget *parent, LoginHandler* loginHandlerEntry, ServerHandler* serverHandlerEntry)
    : QWidget(parent), ui(new Ui::Mods), loginHandler(loginHandlerEntry), serverHandler(serverHandlerEntry)
{
    ui->setupUi(this);
}

Mods::~Mods() {
    delete ui;
}

void Mods::on_BackButton1_clicked() {
    emit S_ChangeForm(1);
}


void Mods::on_BackButton2_clicked() {
    emit S_ChangeForm(1);
}

void Mods::receiveServerId(int serverId) {
    serverHandler->token = loginHandler->token;
    emit S_RequestResult("NUH UH", true);
    return;
    try {
        if (serverHandler->checkToken()) {
            getModList(serverId);
        } else if (loginHandler->checkServerStatus()) {
            int tries = 0;
            bool isSuccess = false;
            while (tries < 3) {
                emit S_UpdateToken();
                tries++;
                if (serverHandler->checkToken()) {
                    isSuccess = true;
                    break;
                }
            }
            if (isSuccess) {
                getModList(serverId);
            } else {
                emit S_RequestResult("Failed to update token", true);
            }
        } else {
            emit S_RequestResult("Connection failed", true);
        }
    } catch (json::parse_error& ex) {
        emit S_RequestResult("Unexpected error", true);
    } catch (std::exception& ex) {
        emit S_RequestResult("Unexpected error", true);
    }
}

void Mods::getModList(int serverId) {
    emit S_RequestResult("", false);
}

void Mods::loadModList(int serverId) {
    emit S_RequestResult("", false);
}
