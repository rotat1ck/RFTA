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
    void receiveUserData(QString username, int rank, bool isServerActive);
    ~Dashboard();

signals:
    void S_ChangeForm(int formId);

    void S_ShowLoadingScreen(QWidget* caller);

    void S_HideLoadingScreen(QWidget* caller);

private slots:
    void initButtonUI(int privileges, bool isServerActive);

    void on_ExitButton1_clicked();

    void on_ExitButton2_clicked();

    void on_StartButton_clicked();

    void on_StopButton_clicked();

    void on_EditServerButton_clicked();

private:
    Ui::Dashboard *ui;
};

#endif // DASHBOARD_H
