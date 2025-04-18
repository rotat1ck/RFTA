#include "mainwindow.h"

#include <QApplication>
#include <QFontDatabase>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    int fontId = QFontDatabase::addApplicationFont(":/fonts/Inter-VariableFont_opsz,wght.ttf");
        if (fontId == -1) {
            qDebug() << "Failed to load font from resource.";
        } else {
            qDebug() << "Font loaded successfully.";
        }


            QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);
            for (const QString &family : fontFamilies) {
                qDebug() << family.toStdString();
            }

        MainWindow w;
        w.show();
        return a.exec();
}
