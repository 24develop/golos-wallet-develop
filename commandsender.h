#ifndef COMMANDSENDER_H
#define COMMANDSENDER_H

#include "command.h"

#include <QObject>

class CommandSender : public QObject
{
    Q_OBJECT
public:
    explicit CommandSender(QObject *parent = nullptr);

signals:
    void response(QString data);

public slots:
    virtual void send(Command *command) = 0;
};

#endif // COMMANDSENDER_H
