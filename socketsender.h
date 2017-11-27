#ifndef WEBSOCKETCLIENT_H
#define WEBSOCKETCLIENT_H

#include "command.h"
#include "commandsender.h"

#include <QtWebSockets/QWebSocket>

class SocketSender : public CommandSender {
Q_OBJECT
public:
    explicit SocketSender(const QUrl &url, QObject *parent = nullptr);

private:
    QWebSocket _socket;
    QUrl _url;

signals:

    void closed();

public slots:

    void connected();

    void send(Command *command) override;
};

#endif // WEBSOCKETCLIENT_H
