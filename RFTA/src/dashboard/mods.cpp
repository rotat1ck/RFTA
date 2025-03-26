#include "../../header/dashboard/mods.h"
#include "ui_mods.h"

Mods::Mods(QWidget *parent, LoginHandler* loginHandlerEntry, ServerHandler* serverHandlerEntry)
    : QWidget(parent), ui(new Ui::Mods), loginHandler(loginHandlerEntry), serverHandler(serverHandlerEntry)
{
    ui->setupUi(this);
    ui->modsScroll->setStyleSheet(scrollstyle);
    modsLayout = new QVBoxLayout(ui->modsScrollContent);

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
    try {
        if (serverHandler->checkToken()) {
            getServerData(serverId);
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
                getServerData(serverId);
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

void Mods::getServerData(int serverId) {
    auto res = serverHandler->getModPack(serverId);
    if (res.status != 200) {
        emit S_RequestResult("Failed to get modpack", true);
        return;
    }

    modList.clear();
    json mods = json::parse(res.message);
    for (auto mod : mods["mods"]) {
        modList.push_back(mod);
    }

    res = serverHandler->getServer(serverId);
    if (res.status != 200) {
        emit S_RequestResult("Failed to get server info", true);
        return;
    }

    json server = json::parse(res.message);
    server = server["server"];

    QString branchname = QString::fromStdString(server["name"]);
    QString core = QString::fromStdString(server.contains("core") && !server["core"].is_null() ? server["core"].get<std::string>() : "");
    QString version = QString::fromStdString(server.contains("version") && !server["version"].is_null() ? server["version"].get<std::string>() : "");
    ui->BranchName->setText(branchname);
    ui->Core->setText(core);
    ui->Version->setText(version);
    loadModList();
}


void Mods::loadModList() {
    if (modsLayout) {
        QLayoutItem* item;
        while ((item = modsLayout->takeAt(0))) {
            delete item->widget();
            delete item;
        }
    }

    for (auto mod : modList) {
        QString modName = QString::fromStdString(mod);
        QPushButton* button = new QPushButton(modName, this);
        button->setCursor(Qt::PointingHandCursor);
        button->setFixedSize(450, 25);
        button->setStyleSheet("background: #9B9B9B;");

        connect(button, &QPushButton::clicked, this, [this, mod]() {
            qDebug() << "Clicked on mod: " + QString::fromStdString(mod);
        });

        modsLayout->addWidget(button);
    }

    emit S_RequestResult("", false);
}
