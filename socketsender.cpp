#include "socketsender.h"
#include <QtCore/QDebug>

SocketSender::SocketSender(const QUrl &url, QObject *parent): CommandSender(parent),
    _url(url)
{
    connect(&this->_socket, &QWebSocket::connected, this, &SocketSender::on_connected);
    connect(&this->_socket, &QWebSocket::disconnected, this, &SocketSender::closed);

    this->_socket.open(QUrl(url));
}

void SocketSender::on_connected()
{
    connect(&this->_socket, &QWebSocket::textMessageReceived, this, &SocketSender::on_response);

    qDebug() << "Socket connected!";
}

void SocketSender::on_response(QString response)
{
    qDebug() << "Response: " << response;

    this->response(response);
}

void SocketSender::send(Command *command)
{
    this->_socket.sendTextMessage(command->toJSON());
}
