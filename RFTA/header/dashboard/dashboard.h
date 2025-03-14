#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QWidget>
#include "../net/serverHandler.h"
#include "../utils/json.hpp"

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
    // - - NET - -
    void S_InitReady();
    void S_CreateNetServerHandler(ServerHandler* handler);

    // - - UI - -
    void S_ChangeForm(int formId);
    void S_ShowLoadingScreen(QWidget* caller);
    void S_HideLoadingScreen(QWidget* caller);

private slots:
    void initButtonUI(int privileges, bool isServerActive);

    void enableStartButton();
    void disableStartButton();
    void enableStopButton();
    void disableStopButton();

    void on_ExitButton1_clicked();
    void on_ExitButton2_clicked();

    void on_StartButton_clicked();
    void on_StopButton_clicked();
    void on_EditServerButton_clicked();

    void on_EditMPButton_clicked();

private:
    Ui::Dashboard *ui;
};

#endif // DASHBOARD_H
