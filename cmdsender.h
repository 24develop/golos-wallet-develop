#ifndef CMD_H
#define CMD_H

#include "command.h"
#include "commandsender.h"

#include <QProcess>

class CmdSender : CommandSender {
Q_OBJECT
public:
    explicit CmdSender(QObject *parent = nullptr);

private:
    QProcess *_current;

public slots:

    void send(Command *command) override;
};

#endif // CMD_H
