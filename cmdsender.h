#ifndef CMD_H
#define CMD_H

#include "command.h"
#include "commandsender.h"

#include <QProcess>

class CmdSender : CommandSender
{
    Q_OBJECT
public:
    explicit CmdSender(QObject *parent = nullptr);

private:
    QProcess *_current;

signals:
    void response(QString data);

public slots:
    void send(Command *command);
};

#endif // CMD_H
