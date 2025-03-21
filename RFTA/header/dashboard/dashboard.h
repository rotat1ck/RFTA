#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QWidget>
#include "../net/loginHandler.h"
#include "../net/serverHandler.h"
#include "../utils/json.hpp"

namespace Ui {
class Dashboard;
}

class Dashboard : public QWidget
{
    Q_OBJECT

public:
    explicit Dashboard(QWidget *parent = nullptr, LoginHandler* loginHandlerEntry = nullptr,
                       ServerHandler* serverHandlerEntry = nullptr);

    void initSequence(QString username, int rank);
    ~Dashboard();

signals:
    // - - UI - -
    void S_ChangeForm(int formId);
    void S_ShowLoadingScreen(QWidget* caller);
    void S_HideLoadingScreen(QWidget* caller);

private slots:
    // - - NET - -
    void getServers(QString username, int rank);


    // - - UI - -
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
    LoginHandler* loginHandler;
    ServerHandler* serverHandler;
};

#endif // DASHBOARD_H
