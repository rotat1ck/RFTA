#ifndef LOADING_H
#define LOADING_H

#include <QWidget>

namespace Ui {
class Loading;
}

class Loading : public QWidget
{
    Q_OBJECT

public:
    explicit Loading(QWidget *parent = nullptr);
    ~Loading();

private:
    Ui::Loading *ui;
};

#endif // LOADING_H
