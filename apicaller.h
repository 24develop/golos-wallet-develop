#ifndef APICALLER_H
#define APICALLER_H

#include "command.h"
#include "commandsender.h"

#include <QObject>
#include <QJsonDocument>

class ApiCaller : public QObject
{
    Q_OBJECT
public:
    explicit ApiCaller(CommandSender *sender, QObject *parent = nullptr);

private:
    CommandSender *_sender;

signals:
    void called(QJsonDocument result);

public slots:
    void call(Command *command);
};

#endif // APICALLER_H
