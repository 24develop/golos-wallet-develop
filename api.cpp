#include <QDebug>

#include "api.h"

Api::Api(ApiCaller *caller, QObject *parent) :
        _caller(caller) {

}

Response *Api::getAccountsCount() {
    return this->_caller->call(new Command(40, "get_accounts_count", new QJsonArray()));
}

Response *Api::getDynamicGlobalProperties() {
    return this->_caller->call(new Command(1, "get_dynamic_global_properties", new QJsonArray()));
}

bool Api::importKey(QString key) {
    auto *params = new QJsonArray();

    params->append(key);

    this->_caller->call(new Command(0, "import_key", params));

    return true;
}

bool Api::transfer(QString from, QString to, QString memo) {
    auto *params = new QJsonArray();

    params->append(from);
    params->append(to);
    params->append("0.1 GPG");
    params->append(memo);
    params->append("true");

    this->_caller->call(new Command(0, "transfer", params));
    return true;
}

Response *Api::getAccount(const QString &name) {
    auto params = new QJsonArray();

    params->append(QJsonArray{name});

    return this->_caller->call(new Command(37, "get_accounts", params));
}
