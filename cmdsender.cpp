#include "cmdsender.h"

#include <QtCore/QDebug>

CmdSender::CmdSender(QObject *parent) : CommandSender(parent)
{
}

void CmdSender::send(Command *command)
{
    this->_current = new QProcess();

    QStringList *args = new QStringList();
    QString fullCommand = "cli-wallet -s wss://ws.golos.io:8090";

    args->append("-c " + command->toString());

    this->_current->start(fullCommand, *args);

    this->_current->waitForFinished();

    QString result = QString::fromStdString(this->_current->readAll().toStdString());

    qDebug() << "CMD result: " << result;

    //this->respond(result);
}
