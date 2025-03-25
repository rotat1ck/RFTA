#ifndef MODS_H
#define MODS_H

#include <QWidget>
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

    // - - UI - -
    void S_ChangeForm(int formId);

private slots:
    void on_BackButton1_clicked();
    void on_BackButton2_clicked();

private:
    Ui::Mods *ui;
    LoginHandler* loginHandler;
    ServerHandler* serverHandler;
};

#endif // MODS_H
