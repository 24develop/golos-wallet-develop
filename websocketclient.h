#ifndef WEBSOCKETCLIENT_H
#define WEBSOCKETCLIENT_H

#include <QObject>
#include <QtWebSockets/QWebSocket>

class WebSocketClient : public QObject
{
    Q_OBJECT
public:
    explicit WebSocketClient(const QUrl &url, QObject *parent = nullptr);

private:
    QWebSocket _socket;
    QUrl _url;

signals:
    void closed();
    void responsed(QString response);

public slots:
    void on_connected();
    void on_response(QString response);
    void send(QString data);
};

#endif // WEBSOCKETCLIENT_H
