#include "command.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QVariant>

Command::Command(int id, QString method, QJsonArray *params) :
        _id(id), _method(method), _params(params) {

}

QString Command::toJSON() {
    QJsonObject result;

    result["method"] = this->_method;
    result["params"] = *this->_params;
    result["id"] = this->_id;

    QJsonDocument document(result);

    return document.toJson(QJsonDocument::Compact);
}

QString Command::toString() {
    QStringList params;
    QVariantList variantParams = this->_params->toVariantList();

    for (auto &variantParam : variantParams) {
        if (variantParam.type() == QVariant::List) {
            params.append("[" + variantParam.toStringList().join(",") + "]");
        }

        params.append(variantParam.toString());
    }

    return this->_method + " " + params.join(" ").trimmed();
}
