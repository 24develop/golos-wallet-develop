//
// Created by artem on 01.12.17.
//

#include "TestTransaction.h"
#include "../socketsender.h"

TestTransaction::TestTransaction(QObject *parent) : QObject(parent) {
    auto *socketSender = new SocketSender(QUrl("wss://ws.golos.io"));
    //auto *socketSender = new SocketSender(QUrl("wss://steemd.steemitdev.com"));
    auto *caller = new ApiCaller(socketSender);
    auto *api = new Api(caller);

    this->_api = api;

    QEventLoop loop;

    connect(socketSender, SIGNAL(sconnect()), &loop, SLOT(quit()));

    loop.exec();
}

void TestTransaction::prepareTransaction() {
    auto *params = new QJsonArray();

    params->append("user");
    params->append("myuser");
    params->append("1.001 GPG");
    params->append("test");

    auto *command = new Command(1, "transfer", params);

    auto *transaction = new Transaction(this->_api, command);

    transaction->prepareTransaction();
}

void TestTransaction::signTransaction() {
    auto *params = new QJsonArray();

    params->append("user");
    params->append("myuser");
    params->append("1.001 GPG");
    params->append("test");

    auto *command = new Command(1, "transfer", params);

    auto *transaction = new Transaction(this->_api, command);

    transaction->prepareTransaction();

    transaction->signTransaction(QString("5JYdb8nw8rmNEABvJTKGounQ6y87MeWauodq17q43tXFFNn57c5"));

    this->_api->call("broadcast_transaction_with_callback", transaction->toJSON());
}

