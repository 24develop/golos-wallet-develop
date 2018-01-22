//
// Created by Artem Antonov on 01.12.17.
//

#ifndef HACKATON_WALLET_TRANSACTION_H
#define HACKATON_WALLET_TRANSACTION_H


#include <QtCore/QObject>
#include <QJsonObject>

class Api;

class Command;

class Transaction : public QObject {
Q_OBJECT

public:
    Transaction(Api *api, Command *command, QObject *parent = nullptr);

    void prepareTransaction();

    void signTransaction(QString wif);

    QJsonObject toJSON();

    QString signature() {
        return this->_signature;
    }

private:
    Api *_api;
    Command *_command;

    uint _ref_block_num;
    uint _ref_block_prefix;
    uint _expiration;

    QString _expirationIso;
    QString _signature;
};


#endif //HACKATON_WALLET_TRANSACTION_H
