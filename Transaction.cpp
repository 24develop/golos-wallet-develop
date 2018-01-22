//
// Created by Artem Antonov on 01.12.17.
//

#include <QtCore/QDateTime>
#include <QDebug>
#include <QtEndian>
#include <QtCore/QCryptographicHash>

#include "Transaction.h"
#include "Response.h"
#include "lib/Auth.h"

#include "api.h"
#include "lib/Signer.h"

#define EXPIRATION_TIME 60

Transaction::Transaction(Api *api, Command *command, QObject *parent) :
        _api(api), _command(command), QObject(parent) {}

void Transaction::prepareTransaction() {
    Response *data = this->_api->getDynamicGlobalProperties();

    QString time = data->getResult().toObject()["time"].toString() + "Z";

    qDebug() << "Time: " << time;

    uint unixTime = QDateTime::fromString(time, Qt::ISODate).toTime_t();
    uint expiration = unixTime + EXPIRATION_TIME;

    this->_expirationIso = QDateTime::fromSecsSinceEpoch(expiration, Qt::UTC).toString(Qt::ISODate);

    uint refBlockNum = (uint) (data->getResult().toObject()["head_block_number"].toInt() - 3) & 0xFFFF;

    Response *blockData = this->_api->getBlock(data->getResult().toObject()["head_block_number"].toInt() - 2);

    auto headBlockId = QByteArray::fromHex(blockData->getResult().toObject()["previous"].toString().toUtf8());

    this->_expirationIso.replace('Z', "");

    this->_expiration = expiration;
    this->_ref_block_num = refBlockNum;
    this->_ref_block_prefix = qToBigEndian(headBlockId.mid(4, 4).toHex().toUInt(nullptr, 16));

    qDebug() << "Expiration: " << this->_expiration;
    qDebug() << "Expiration ISO: " << this->_expirationIso;
    qDebug() << "Ref block num: " << this->_ref_block_num;
    qDebug() << "Ref block prefix: " << this->_ref_block_prefix;
}

void Transaction::signTransaction(QString wif) {
    auto privateKeyBuffer = Auth::fromWif(wif);

    qDebug() << "Private key char: " << privateKeyBuffer.toHex(' ');
    qDebug() << "Private key buffer: " << privateKeyBuffer;

    auto transaction = QByteArray::number(qToBigEndian((uint16_t) this->_ref_block_num), 16)
            .append(QByteArray::number(qToBigEndian((uint32_t) this->_ref_block_prefix), 16))
            .append(QByteArray::number(qToBigEndian((uint32_t) this->_expiration), 16));

    transaction = QByteArray::fromHex(transaction).append(this->_command->toBuffer());

    //auto chainId = QByteArray::fromHex("0000000000000000000000000000000000000000000000000000000000000000");
    auto chainId = QByteArray::fromHex("782a3039b478c839e4cb0c941ff4eaeb7df40bdd68bd441afd444b9da763de12");

    transaction = chainId.append(transaction);

    qDebug() << "Transaction: " << transaction.toHex(' ');

    transaction = QCryptographicHash::hash(transaction, QCryptographicHash::Sha256);

    qDebug() << "Transaction hash: " << transaction.toHex(' ');

    auto signature = Signer::sign(privateKeyBuffer, transaction);

    qDebug() << "Verified: " << Signer::verify(signature, transaction);

    qDebug() << "Signature raw: " << signature;
    qDebug() << "Signature hex: " << signature.toHex(' ');

    this->_signature = signature.toHex();
}

QJsonObject Transaction::toJSON() {
    QJsonObject result;

    QJsonArray operations;
    QJsonArray operation;
    QJsonArray extensions;
    QJsonArray signatures;

    operation.append(this->_command->getMethod());

    auto *objectParams = new QJsonObject();

    auto commandParams = this->_command->getParams();

    qDebug() << "Params size: " << commandParams->size();

    objectParams->insert("from", commandParams->at(0));
    objectParams->insert("to", commandParams->at(1));
    objectParams->insert("amount", commandParams->at(2));
    objectParams->insert("memo", commandParams->at(3));

    operation.append(*objectParams);

    operations.append(operation);

    qDebug() << "Zero: " << this->_signature;

    signatures.append(this->_signature);

    result["ref_block_num"] = (qint64) this->_ref_block_num;
    result["ref_block_prefix"] = (qint64) this->_ref_block_prefix;
    result["expiration"] = this->_expirationIso;

    result["operations"] = operations;
    result["extensions"] = extensions;
    result["signatures"] = signatures;

    return result;
}
