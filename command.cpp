#include "command.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QVariant>
#include <QDebug>

#define STEEM_SYMBOL (uint64_t(3) | (uint64_t('G') << 8) | (uint64_t('O') << 16) | (uint64_t('L') << 24) | (uint64_t('O') << 32) | (uint64_t('S') << 40)) ///< STEEM with 3 digits of precision

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

QByteArray Command::toBuffer() {
    if (this->_method == "transfer") {
        auto amount = this->_params->at(2).toString().split(' ');

        auto dotIndex = amount[0].indexOf('.');
        uint64_t pay = amount[0].remove('.').toUInt();
        auto precision = dotIndex == -1 ? 0 : amount[0].length() - 1;

        auto currency = amount[1];

        auto *buf = new QByteArray(7, 0);
        buf->insert(0, currency.toUtf8());

        qDebug() << "Currency: " << buf->toHex(' ');

        auto serialized = QByteArray()
                .append((char) this->_id)
                .append(2)
                .append((char) this->_params->at(0).toString().size())
                .append(this->_params->at(0).toString().toUtf8())
                .append((char) this->_params->at(1).toString().size())
                .append(this->_params->at(1).toString().toUtf8())
                .append(reinterpret_cast<const char *>(&pay), sizeof(pay))
                .append((char) precision)
                .append(buf->mid(0, 7))
                .append((char) this->_params->at(3).toString().size())
                .append(this->_params->at(3).toString().toUtf8())
                .append((char) 0);

        qDebug() << "Serialized: " << serialized.toHex(' ');

        return serialized;
    } else {
        return QByteArray();
    }
}

const QString &Command::getMethod() const {
    return _method;
}

QJsonArray *Command::getParams() const {
    return _params;
}
