#ifndef API_H
#define API_H

#include "apicaller.h"

#include <QObject>

class Api : public QObject
{
    Q_OBJECT
public:
    explicit Api(ApiCaller *caller, QObject *parent = nullptr);

    int getAccountsCount();
    bool importKey(QString key);
    bool transfer(QString from, QString to, QString memo);

private:
    ApiCaller *_caller;

signals:

public slots:
};

#endif // API_H
