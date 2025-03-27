#include "../../header/dashboard/mods.h"
#include "ui_mods.h"

Mods::Mods(QWidget *parent, LoginHandler* loginHandlerEntry, ServerHandler* serverHandlerEntry)
    : QWidget(parent), ui(new Ui::Mods), loginHandler(loginHandlerEntry), serverHandler(serverHandlerEntry)
{
    ui->setupUi(this);
    ui->modsScroll->setStyleSheet(scrollstyle);
    modsLayout = new QVBoxLayout(ui->modsScrollContent);
    modsLayout->setAlignment(Qt::AlignTop);
    // modsLayout->setContentsMargins(5, 10, 5, 0);
    // modsLayout->setSpacing(5);
    ui->LoadJarProgress->setStyleSheet(progressBarStyle);
    ui->LoadZipProgress->setStyleSheet(progressBarStyle);

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
            initModsData(serverId);
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
                initModsData(serverId);
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

void Mods::initModsData(int serverId) {
    currentServerId = serverId;
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


        if (mod != modList.at(0)) {
            button->setStyleSheet(inactiveModsButtonStyle);
        } else {
            button->setStyleSheet(activeModsButtonStyle);
        }

        connect(button, &QPushButton::clicked, this, [this, mod, button]() {
            for (int i = 0; i < modsLayout->count(); ++i) {
                QLayoutItem* item = modsLayout->itemAt(i);
                QPushButton* btn = qobject_cast<QPushButton*>(item->widget());
                btn->setStyleSheet(inactiveModsButtonStyle);
            }

            button->setStyleSheet(activeModsButtonStyle);
            currentMod = button;
        });

        modsLayout->addWidget(button);
    }

    emit S_RequestResult("", false);
}

void Mods::on_LoadJarButton_clicked() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Select .jar file"), "", tr("JAR Files (*.jar)"));

    connect(serverHandler, &ServerHandler::uploadProgress, this, [this](int progress) {
        ui->LoadJarProgress->setValue(progress);
    });

    connect(serverHandler, &ServerHandler::uploadFinished, this, [this](bool success) {
        if (success) {
            ui->LoadJarProgress->setValue(100);
            Mods::initModsData(currentServerId);
            emit S_Infobar(this, "File uploaded successfully", false);
        } else {
            emit S_Infobar(this, "Failed to upload the file", true);
        }
    });

    if (fileName != "") {
        serverHandler->loadJar(currentServerId, fileName);
    } else {
        emit S_Infobar(this, "Operation canceled", true);
    }
}


void Mods::on_LoadZipButton_clicked() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Select .zip archive"), "", tr("ZIP Archives (*.zip)"));

    connect(serverHandler, &ServerHandler::uploadProgress, this, [this](int progress) {
        ui->LoadZipProgress->setValue(progress);
    });

    connect(serverHandler, &ServerHandler::uploadFinished, this, [this](bool success) {
        if (success) {
            ui->LoadZipProgress->setValue(100);
            Mods::initModsData(currentServerId);
            emit S_Infobar(this, "File uploaded successfully", false);
        } else {
            emit S_Infobar(this, "Failed to upload the file", true);
        }
    });

    if (fileName != "") {
        serverHandler->loadZip(currentServerId, fileName);
    } else {
        emit S_Infobar(this, "Operation canceled", true);
    }
}
