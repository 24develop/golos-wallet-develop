#include "commandsender.h"

CommandSender::CommandSender(QObject *parent) : QObject(parent) {

}

void CommandSender::responded(QString data) {
    auto commandResultDocument = QJsonDocument::fromJson(data.toUtf8());

    this->respond(new Response(data));
}
