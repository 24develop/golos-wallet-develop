#ifndef API_H
#define API_H

#include "apicaller.h"
#include "Response.h"
#include "Transaction.h"

#include <QObject>

class Api : public QObject {
Q_OBJECT
public:
    explicit Api(ApiCaller *caller, QObject *parent = nullptr);

    Response *getAccountsCount();

    Response *getAccount(const QString &name);

    bool importKey(QString key);

    Response *transfer(QString wif, QString from, QString to, QString amount, QString memo);

    Response *getDynamicGlobalProperties();

    Response *getBlock(int number);

    Response *broadcastTransaction(Transaction *transaction);

    Response *login(QString name, QString password);

    Response *call(QString method, QJsonObject params);

    Response *getApiId(QString group);

    int getCallId();

    void init();

private:
    ApiCaller *_caller;
    int _callId = 1;

    int _dbCallId;
    int _followCallId;
    int _networkCallId;
    int _loginCallId;

signals:

    void getAccountRespond(Response *response);

    void getDynamicGlobalPropertiesRespond(Response *response);

public slots:
};

#endif // API_H
