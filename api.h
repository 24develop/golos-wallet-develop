#ifndef API_H
#define API_H

#include "apicaller.h"
#include "Response.h"

#include <QObject>

class Api : public QObject {
Q_OBJECT
public:
    explicit Api(ApiCaller *caller, QObject *parent = nullptr);

    void getAccountsCount();

    void getAccount(const QString &name);

    bool importKey(QString key);

    bool transfer(QString from, QString to, QString memo);

private:
    ApiCaller *_caller;

public slots:

    void listener(Response *response);

signals:

    void getAccountRespond(Response *response);

public slots:
};

#endif // API_H
