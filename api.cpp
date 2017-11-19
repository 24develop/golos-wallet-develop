#include "api.h"

Api::Api(ApiCaller *caller, QObject *parent):
    _caller(caller)
{

}

int Api::getAccountsCount()
{
    this->_caller->callCmd(new Command(40, "get_accounts_count", new QStringList()));

    return 1;
}

bool Api::importKey(QString key)
{
    QStringList *params = new QStringList();

    params->append(key);

    this->_caller->callCmd(new Command(0, "import_key", params));

    return true;
}

bool Api::transfer(QString from, QString to, QString memo)
{
    QStringList *params = new QStringList();

    params->append(from);
    params->append(to);
    params->append("0.1 GPG");
    params->append(memo);
    params->append("true");

    this->_caller->callCmd(new Command(0, "transfer", params));
    return true;
}
