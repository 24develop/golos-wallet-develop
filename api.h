#ifndef API_H
#define API_H

#include "apicaller.h"
#include "Response.h"

#include <QObject>

class Api : public QObject {
Q_OBJECT
public:
    explicit Api(ApiCaller *caller, QObject *parent = nullptr);

    Response *getAccountsCount();

    Response *getAccount(const QString &name);

    bool importKey(QString key);

    bool transfer(QString from, QString to, QString memo);

    Response *getDynamicGlobalProperties();

private:
    ApiCaller *_caller;

signals:

    void getAccountRespond(Response *response);

    void getDynamicGlobalPropertiesRespond(Response *response);

public slots:
};

#endif // API_H
