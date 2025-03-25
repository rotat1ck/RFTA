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
    qDebug() << serverId;
}
