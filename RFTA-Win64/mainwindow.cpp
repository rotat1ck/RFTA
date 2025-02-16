#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void LoginFunc() {
    qDebug() << "LoginFunc";
}

void MainWindow::on_LoginButton_clicked()
{
    LoginFunc();
}


void MainWindow::on_PasswordInput_returnPressed()
{
    LoginFunc();
}

