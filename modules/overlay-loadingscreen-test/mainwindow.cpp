#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent) {
    login = new Login(this);

    layout = new QStackedLayout;
    layout->addWidget(login);

    layout->setCurrentWidget(login);

    // QWidget* loadScreen = new QWidget(this);
    // loadScreen->setFixedSize(200, 150);
    // loadScreen->setGeometry(275, 175, 200, 150);
    // loadScreen->setStyleSheet("background: #707070;border-radius: 20px;");


    loadScreen = new Loading(this);
    login->setEnabled(false);
    QTimer::singleShot(3000, this, [this]() {
            loadScreen->hide();
            login->setEnabled(true);
            loadScreen->deleteLater();
    });
}

MainWindow::~MainWindow()
{
}

