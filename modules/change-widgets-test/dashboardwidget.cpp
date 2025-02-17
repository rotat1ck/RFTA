#include "dashboardwidget.h"
#include "ui_dashboardwidget.h"

DashboardWidget::DashboardWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DashboardWidget)
{
    ui->setupUi(this);
}

DashboardWidget::~DashboardWidget()
{
    delete ui;
}

void DashboardWidget::on_pushButton_clicked()
{
    emit SChangeForm(0);
    qDebug() << "Signal to change to login";
}

