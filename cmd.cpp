#include "cmd.h"

#include <QtCore/QDebug>

Cmd::Cmd(QObject *parent) : QObject(parent)
{
}

void Cmd::send(QString data)
{
    this->_current = new QProcess();
    QStringList *args = new QStringList();
    QString command = "cli-wallet -s wss://ws.golos.io:8090";

    connect(this->_current, SIGNAL(readyRead()), this, SLOT(on_response()));

    args->append("-c " + data);

    this->_current->start(command, *args);

    this->_current->waitForFinished();

    QString result = QString::fromStdString(this->_current->readAll().toStdString());

    qDebug() << "CMD result: " << result;
}

void Cmd::on_response()
{
}
