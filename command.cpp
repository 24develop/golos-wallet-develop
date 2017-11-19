#include "command.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

Command::Command(int id, QString method, QStringList* params):
    _id(id), _method(method)
{
    this->_params = params;
}

QString Command::toJSON()
{
    QJsonObject result;

    result["method"] = this->_method;
    result["params"] = QJsonArray::fromStringList(*this->_params);
    result["id"] = this->_id;

    QJsonDocument document(result);

    return document.toJson(QJsonDocument::Compact);
}

QString Command::toString()
{
    return this->_method + " " + this->_params->join(" ");
}
