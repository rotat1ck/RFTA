#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.resize(260, 200);
    w.setWindowTitle("File Uploader");
    w.show();
    return a.exec();
}
