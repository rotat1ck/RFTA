#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QScrollArea>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    QString text =
            "This is a very long text that will be wrapped inside the QLabel. "
            "The QLabel is placed inside a QScrollArea, which is set to have a fixed horizontal size. "
            "This ensures that the text wraps and the scroll area only scrolls vertically.";


    ui->setupUi(this);
    ui->scrollArea->setWidgetResizable(true);

    ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->scrollArea->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

    QLabel *label = new QLabel(text);
    label->setWordWrap(true);

    QVBoxLayout *layout = new QVBoxLayout();

    ui->scrollAreaWidgetContents->setLayout(layout);

    QVBoxLayout* currentLayout = qobject_cast<QVBoxLayout*>(ui->scrollAreaWidgetContents->layout());
    if (currentLayout) {
        currentLayout->addWidget(label);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

