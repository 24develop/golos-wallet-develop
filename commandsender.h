#ifndef COMMANDSENDER_H
#define COMMANDSENDER_H

#include "command.h"
#include "Response.h"

#include <QObject>
#include <QString>
#include <QJsonDocument>

class CommandSender : public QObject {
Q_OBJECT
public:
    explicit CommandSender(QObject *parent = nullptr);

signals:

    void respond(Response *data);

public slots:

    virtual void send(Command *command) = 0;

protected slots:

    void responded(QString data);
};

#endif // COMMANDSENDER_H
