#ifndef WEBSOCKETCLIENT_H
#define WEBSOCKETCLIENT_H

#include "command.h"
#include "commandsender.h"

#include <QtWebSockets/QWebSocket>

class SocketSender : public CommandSender
{
    Q_OBJECT
public:
    explicit SocketSender(const QUrl &url, QObject *parent = nullptr);

private:
    QWebSocket _socket;
    QUrl _url;

signals:
    void closed();
    void response(QString response);

public slots:
    void on_connected();
    void on_response(QString response);
    void send(Command *command);
};

#endif // WEBSOCKETCLIENT_H
