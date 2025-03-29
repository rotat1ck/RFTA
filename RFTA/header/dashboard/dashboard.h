#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QWidget>
#include <QTimer>
#include <vector>
#include <QMap>

#include <QStackedWidget>
#include <QVBoxLayout>
#include <QScrollBar>
#include <QScrollArea>

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
    void editMPAnswerHandler(std::string message, bool isFailure);
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
    void initServersConsoleLayout();
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

    QString insertLineBreaks(QString text, int maxLineLength);
    void addTextConsoleLayout(QString text);
    void setConsoleLayout(int serverId);


private:
    Ui::Dashboard *ui;
    LoginHandler* loginHandler;
    ServerHandler* serverHandler;

    QScrollArea* ConsoleScroll;
    QStackedWidget* ConsoleScrollLayouts;
    QVBoxLayout* serversLayout;
    QMap<int, int> serversConsoleLayout;



    // ==============
    // - - STYLES - -
    // ==============

    QString activeStartButtonStyle =
        "background: rgba(204, 218, 185, 1);"
        "border-radius: 15px;"
        "font-family: 'Inter SemiBold';"
        "font-size: 18px;"
        "line-height: 22px;"
        "color: rgba(50, 50, 50, 1);"
    ;

    QString activeStopButtonStyle =
        "background: rgba(255, 217, 217, 1);"
        "border-radius: 15px;"
        "font-family: 'Inter SemiBold';"
        "font-size: 18px;"
        "line-height: 22px;"
        "color: rgba(50, 50, 50, 1);"
    ;

    QString activeEditButtonStyle =
        "background: rgba(217, 217, 217, 1);"
        "border-radius: 15px;"
        "font-family: 'Inter SemiBold';"
        "font-size: 18px;"
        "line-height: 22px;"
        "color: rgba(50, 50, 50, 1);"
    ;

    QString inactiveStartButtonStyle =
        "background: rgba(204, 218, 185, 128);"
        "border-radius: 15px;"
        "font-family: 'Inter SemiBold';"
        "font-size: 18px;"
        "line-height: 22px;"
        "color: rgba(50, 50, 50, 128);"
    ;

    QString inactiveStopButtonStyle =
        "background: rgba(255, 217, 217, 128);"
        "border-radius: 15px;"
        "font-family: 'Inter SemiBold';"
        "font-size: 18px;"
        "line-height: 22px;"
        "color: rgba(50, 50, 50, 128);"
    ;

    QString activeServerButtonStyle =
        "background: rgba(155, 155, 155, 1);"
        "border-radius: 15px;"
        "font-family: 'Inter SemiBold';"
        "font-size: 18px;"
        "line-height: 22px;"
        "color: rgba(0, 0, 0, 1);"
    ;

    QString inactiveServerButtonStyle =
        "background: rgba(124, 124, 124, 76);"
        "border-radius: 15px;"
        "font-family: 'Inter SemiBold';"
        "font-size: 18px;"
        "line-height: 22px;"
        "color: rgba(0, 0, 0, 76);"
    ;

    QString scrollAreaStyle =
        "QScrollArea { border: none; }"
        "QScrollBar:vertical { border: none; background: #D9D9D9; width: 10px; }"
        "QScrollBar::handle:vertical { background: #707070; min-height: 20px; }"
    ;

    QString stackedLayoutTextStyle =
        "font-family: 'Inter SemiBold';"
        "font-size: 15px;"
        "line-height: 17px;"
        "color: #CDCDCD;"
    ;
};

#endif // DASHBOARD_H
