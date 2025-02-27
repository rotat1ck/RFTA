#include "../header/loadingscreen.h"
#include "ui_loadingscreen.h"

LoadingScreen::LoadingScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoadingScreen)
{
    ui->setupUi(this);
    QMovie* gif = new QMovie(":/img/LoadWheel.gif");
    ui->gifLabel->setMovie(gif);
    ui->gifLabel->setScaledContents(true);
    gif->start();
}

LoadingScreen::~LoadingScreen() {
    delete ui;
}
