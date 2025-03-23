#ifndef MODS_H
#define MODS_H

#include <QWidget>

namespace Ui {
class Mods;
}

class Mods : public QWidget
{
    Q_OBJECT

public:
    explicit Mods(QWidget *parent = nullptr);
    ~Mods();

private:
    Ui::Mods *ui;
};

#endif // MODS_H
