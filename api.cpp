#include <QDebug>

#include "api.h"

Api::Api(ApiCaller *caller, QObject *parent) :
        _caller(caller) {
}

Response *Api::getAccountsCount() {
    return this->_caller->call(new Command(this->getCallId(), "get_accounts_count", new QJsonArray()));
}

Response *Api::getDynamicGlobalProperties() {
    QJsonArray params;
    QJsonArray methodParams;

    params.append(this->_dbCallId);
    params.append("get_dynamic_global_properties");
    params.append(methodParams);

    return this->_caller->call(new Command(0, "call", &params));
}

bool Api::importKey(QString key) {
    auto *params = new QJsonArray();

    params->append(key);

    this->_caller->call(new Command(this->getCallId(), "import_key", params));

    return true;
}

Response *Api::transfer(QString wif, QString from, QString to, QString amount, QString memo) {
    auto *params = new QJsonArray();

    params->append(from);
    params->append(to);
    params->append(amount);
    params->append(memo);
    params->append("true");

    auto transaction = new Transaction(this, new Command(1, "transfer", params));

    transaction->prepareTransaction();
    transaction->signTransaction(wif);

    const auto validatedResponse = this->validateTransaction(transaction);

    qDebug() << "Validation result: " << validatedResponse->getResult().toString();

    return this->broadcastTransaction(transaction);
}

Response *Api::getAccount(const QString &name) {
    auto params = new QJsonArray();

    params->append(QJsonArray{name});

    return this->_caller->call(new Command(this->getCallId(), "get_accounts", params));
}

Response *Api::getBlock(int number) {
    QJsonArray params;
    QJsonArray methodParams;

    methodParams.append(number);

    params.append(this->_dbCallId);
    params.append("get_block");

    params.append(methodParams);

    return this->_caller->call(new Command(this->getCallId(), "call", &params));
}

Response *Api::broadcastTransaction(Transaction *transaction) {
    this->call("broadcast_transaction_synchronous", transaction->toJSON());
}

Response *Api::call(QString method, QJsonObject params) {
    auto _params = new QJsonArray();

    auto callParams = new QJsonArray();
    //callParams->append(QJsonValue::Null);
    callParams->append(params);

    _params->append(this->_networkCallId);
    _params->append(method);
    _params->append(*callParams);

    return this->_caller->call(new Command(this->getCallId(), "call", _params));
}

Response *Api::login(QString name, QString password) {
    QJsonArray params;
    QJsonArray loginParams;

    loginParams.append(name);
    loginParams.append(password);

    params.append(this->_loginCallId);
    params.append("login");
    params.append(loginParams);

    return this->_caller->call(new Command(this->getCallId(), "call", &params));
}

int Api::getCallId() {
    return this->_callId++;
}

Response *Api::getApiId(QString group) {
    QJsonArray params;
    QJsonArray methodParams;

    methodParams.append(group);

    params.append(1);
    params.append("get_api_by_name");
    params.append(methodParams);

    return this->_caller->call(new Command(this->getCallId(), "call", &params));
}

void Api::init() {
    this->_dbCallId = this->getApiId("database_api")->getResult().toInt();
    this->_loginCallId = this->getApiId("login_api")->getResult().toInt();
    this->_followCallId = this->getApiId("follow_api")->getResult().toInt();
    this->_networkCallId = this->getApiId("network_broadcast_api")->getResult().toInt();
}

Response *Api::validateTransaction(Transaction *transaction) {
    QJsonArray params;
    QJsonArray methodParams;

    methodParams.append(transaction->toJSON());

    params.append(this->_dbCallId);
    params.append("verify_authority");
    params.append(methodParams);

    return this->_caller->call(new Command(this->getCallId(), "call", &params));
}
