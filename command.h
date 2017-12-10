#ifndef COMMAND_H
#define COMMAND_H

#include <QString>
#include <QStringList>
#include <QtCore/QJsonObject>

class Command {
private:
    int _id;
    QString _method;
    QJsonArray *_params;

public:
    Command(int id, QString method, QJsonArray *params);

    QString toJSON();

    QString toString();

    QByteArray toBuffer();

    const QString &getMethod() const;

    QJsonArray *getParams() const;
};

#endif // COMMAND_H
