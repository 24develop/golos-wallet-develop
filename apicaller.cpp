#include <QtCore/QEventLoop>
#include <QDebug>

#include "apicaller.h"

ApiCaller::ApiCaller(CommandSender *sender, QObject *parent) :
        _sender(sender) {
    connect(this->_sender, SIGNAL(respond(Response * )), this, SLOT(_responded(Response * )));
}

Response *ApiCaller::call(Command *command) {
    QEventLoop loop;

    connect(this->_sender, SIGNAL(respond(Response * )), &loop, SLOT(quit()));

    this->_sender->send(command);

    loop.exec();

    qDebug() << "Response from loop: " << this->_lastResponse->getId();

    return this->_lastResponse;
}

void ApiCaller::_responded(Response *response) {
    this->_lastResponse = response;

    this->respond(response);
}
