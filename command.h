#ifndef COMMAND_H
#define COMMAND_H

#include <QString>
#include <QStringList>

class Command
{
private:
    int _id;
    QString _method;
    QStringList* _params;

public:
    Command(int id, QString method, QStringList* params);

    QString toJSON();
    QString toString();
};

#endif // COMMAND_H
