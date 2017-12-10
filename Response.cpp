//
// Created by artem on 26.11.17.
//

#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QDebug>

#include "Response.h"

Response::Response(QString rawResponse) {
    qDebug() << "Response: " << rawResponse;

    auto commandResultDocument = QJsonDocument::fromJson(rawResponse.toUtf8());
    QJsonObject commandResultObject = commandResultDocument.object();

    this->_id = commandResultObject["id"].toInt();

    this->_result = commandResultObject["result"];
}
