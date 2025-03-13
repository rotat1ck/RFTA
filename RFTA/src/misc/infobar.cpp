#include "../../header/misc/infobar.h"

InfoBar::InfoBar(QWidget *parent, std::string infoMessage) :QWidget(parent) {
    setGeometry(100, 460, 550, 30);
    infoLabel = new QLabel(this);
    infoLabel->setGeometry(0, 0, 550, 30);
    infoLabel->setAlignment(Qt::AlignCenter);
}

InfoBar::~InfoBar() {

}

void InfoBar::displayMessage(std::string message, bool isFailure) {
    QString infoMessage = QString::fromStdString(message);
    infoLabel->setText(QString(infoMessage));
    if (isFailure) {
        this->setStyleSheet(failureInfoBarStyleSheet);
    } else {
        this->setStyleSheet(successInfoBarStyleSheet);
    }
}
