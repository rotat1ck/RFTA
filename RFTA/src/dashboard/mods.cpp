#include "../../header/dashboard/mods.h"
#include "ui_mods.h"

Mods::Mods(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Mods)
{
    ui->setupUi(this);
}

Mods::~Mods()
{
    delete ui;
}
