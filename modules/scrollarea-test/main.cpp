#include <QApplication>

#include "mainwindow.h"

class ScrollableLabel : public QWidget {
public:
    ScrollableLabel(const QString &text, QWidget *parent = nullptr)
        : QWidget(parent) {

    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow w;
    w.show();
    return app.exec();
}
