#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QWidget>
#include <QVBoxLayout>

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
    // - - NET - -
    void S_UpdateToken();
    void S_EditMPSendData(int serverId);
    void S_EditServerSendData(int serverId);

    // - - UI - -
    void S_ChangeForm(int formId);
    void S_Infobar(QWidget* caller, std::string, bool isFailure);
    void S_ShowLoadingScreen(QWidget* caller);
    void S_HideLoadingScreen(QWidget* caller);

private slots:
    // - - NET - -
    void initBranches(QString username, int rank);
    void getServers();
    void uptadeServerList();


    // - - UI - -
    void initButtonUI(QString username, int privileges, ServerHandler::Server);
    void enableStartButton();
    void disableStartButton();
    void enableStopButton();
    void disableStopButton();
    void on_ExitButton1_clicked();
    void on_ExitButton2_clicked();
    void startButtonHandler(int serverId);
    void stopButtonHandler(int serverId);
    void editMPButtonHandler(int serverId);
    void editServerButtonHandler(int serverId);

private:
    Ui::Dashboard *ui;
    LoginHandler* loginHandler;
    ServerHandler* serverHandler;
    QVBoxLayout* serversLayout;
};

#endif // DASHBOARD_H
