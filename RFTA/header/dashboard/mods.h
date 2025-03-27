#ifndef MODS_H
#define MODS_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QFileDialog>
#include <vector>

#include "../net/loginHandler.h"
#include "../net/serverHandler.h"

namespace Ui {
class Mods;
}

class Mods : public QWidget
{
    Q_OBJECT

public:
    explicit Mods(QWidget *parent = nullptr, LoginHandler* loginHandlerEntry = nullptr, ServerHandler* serverHandlerEntry = nullptr);
    ~Mods();
    void receiveServerId(int serverId);

signals:
    // - - NET - -
    void S_UpdateToken();
    void S_RequestResult(std::string message, bool isFailure);

    // - - UI - -
    void S_ChangeForm(int formId);
    void S_Infobar(QWidget* caller, std::string, bool isFailure);
    void S_ShowLoadingScreen(QWidget* caller);
    void S_HideLoadingScreen(QWidget* caller);

private slots:
    // - - NET - -
    void initModsData(int serverId);

    // - - UI - -
    void on_BackButton1_clicked();
    void on_BackButton2_clicked();
    void loadModList();

    void on_LoadJarButton_clicked();

    void on_LoadZipButton_clicked();

private:
    Ui::Mods *ui;
    int currentServerId;
    LoginHandler* loginHandler;
    ServerHandler* serverHandler;
    QPushButton* currentMod;
    std::vector<std::string> modList;
    QVBoxLayout* modsLayout;

    QString scrollstyle =
        "QScrollArea { border: none; }"
        "QScrollBar:vertical { border: none; background: #D9D9D9; width: 10px; }"
        "QScrollBar::handle:vertical { background: #707070; min-height: 20px; }"
    ;

    QString progressBarStyle =
        "QProgressBar {"
            "background: #373333;"
            "border-radius: 5px;"
            "font-family: 'Inter SemiBold';"
            "font-size: 18px;"
            "line-height: 22px;"
            "color: #FFFFFF;"
        "}"
        "QProgressBar::chunk {"
        "    background: #707070;"
        "    border-radius: 5px;"
        "}"

    ;

    QString activeModsButtonStyle =
        "background: rgba(155, 155, 155, 1);"
        "border-radius: 5px;"
        "padding-left: 5px;"
        "font-family: 'Inter SemiBold';"
        "font-size: 18px;"
        "line-height: 22px;"
        "text-align:left;"
        "color: rgba(0, 0, 0, 1);"
    ;

    QString inactiveModsButtonStyle =
        "background: rgba(124, 124, 124, 1);"
        "border-radius: 5px;"
        "padding-left: 5px;"
        "font-family: 'Inter SemiBold';"
        "font-size: 18px;"
        "line-height: 22px;"
        "text-align:left;"
        "color: rgba(0, 0, 0, 76);"
    ;
};

#endif // MODS_H
