#ifndef MODS_H
#define MODS_H

#include <QWidget>
#include <QVBoxLayout>
#include <QTimer>
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
    void getServerData(int serverId);

    // - - UI - -
    void on_BackButton1_clicked();
    void on_BackButton2_clicked();
    void loadModList();

private:
    Ui::Mods *ui;
    LoginHandler* loginHandler;
    ServerHandler* serverHandler;
    std::vector<std::string> modList;
    QVBoxLayout* modsLayout;

    QString scrollstyle =
        "QScrollArea { border: none; }"
        "QScrollBar:vertical { border: none; background: #f0f0f0; width: 10px; }"
        "QScrollBar::handle:vertical { background: #a0a0a0; min-height: 20px; }"
        "QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical { background: none; }"
        "QScrollBar::up-arrow:vertical, QScrollBar::down-arrow:vertical { background: none; }"
    ;

};

#endif // MODS_H
