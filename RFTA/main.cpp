#include "header/mainwindow.h"

#include <QApplication>
#include <QFontDatabase>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFontDatabase::addApplicationFont(":/fonts/Inter-VariableFont_opsz,wght.ttf");
    MainWindow w;
    w.setFixedSize(QSize(750, 500));;
    w.show();
    return a.exec();
}
