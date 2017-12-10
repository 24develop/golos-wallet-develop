#include "socketsender.h"

SocketSender::SocketSender(const QUrl &url, QObject *parent): CommandSender(parent),
    _url(url)
{
    connect(&this->_socket, &QWebSocket::connected, this, &SocketSender::connected);
    connect(&this->_socket, &QWebSocket::disconnected, this, &SocketSender::closed);

    this->_socket.open(QUrl(url));
}

void SocketSender::connected() {
    connect(&this->_socket, &QWebSocket::textMessageReceived, this, &SocketSender::responded);

    qDebug() << "Socket connected!";

    this->sconnect();
}

void SocketSender::send(Command *command)
{
    qDebug() << "Request: " << command->toJSON();

    this->_socket.sendTextMessage(command->toJSON());
}
