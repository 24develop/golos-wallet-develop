#ifndef APICALLER_H
#define APICALLER_H

#include "command.h"
#include "commandsender.h"

#include <QObject>
#include <QJsonDocument>

class ApiCaller : public QObject {
Q_OBJECT
public:
    explicit ApiCaller(CommandSender *sender, QObject *parent = nullptr);

private:
    CommandSender *_sender;
    Response *_lastResponse;

private slots:

    void _responded(Response *response);

signals:

    void respond(Response *response);

public slots:

    Response *call(Command *command);
};

#endif // APICALLER_H
