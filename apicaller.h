#ifndef APICALLER_H
#define APICALLER_H

#include "cmd.h"
#include "command.h"
#include <websocketclient.h>

#include <QObject>
#include <QJsonDocument>

class ApiCaller : public QObject
{
    Q_OBJECT
public:
    explicit ApiCaller(WebSocketClient *sc, Cmd *cmd, QObject *parent = nullptr);

private:
    WebSocketClient *_socket;
    Cmd *_cmd;

signals:
    void called(QJsonDocument result);

public slots:
    void call(Command *command);
    void callCmd(Command *command);
};

#endif // APICALLER_H
