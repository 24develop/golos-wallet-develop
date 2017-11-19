#include "websocketclient.h"
#include <QtCore/QDebug>

WebSocketClient::WebSocketClient(const QUrl &url, QObject *parent):
    _url(url)
{
    connect(&this->_socket, &QWebSocket::connected, this, &WebSocketClient::on_connected);
    connect(&this->_socket, &QWebSocket::disconnected, this, &WebSocketClient::closed);

    this->_socket.open(QUrl(url));
}

void WebSocketClient::on_connected()
{
    connect(&this->_socket, &QWebSocket::textMessageReceived, this, &WebSocketClient::on_response);

    qDebug() << "Socket connected!";
}

void WebSocketClient::on_response(QString response)
{
    qDebug() << "Response: " << response;

    this->responsed(response);
}

void WebSocketClient::send(QString data)
{
    this->_socket.sendTextMessage(data);
}
