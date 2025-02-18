#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QWidget>

namespace Ui {
class Dashboard;
}

class Dashboard : public QWidget
{
    Q_OBJECT

public:
    explicit Dashboard(QWidget *parent = nullptr);
    void receiveUserData(QString username, int rank);
    ~Dashboard();

signals:
    void SChangeForm(int formId);

private slots:
    void on_pushButton_clicked();



private:
    Ui::Dashboard *ui;
};

#endif // DASHBOARD_H
