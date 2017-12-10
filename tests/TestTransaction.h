//
// Created by artem on 01.12.17.
//

#ifndef HACKATON_WALLET_TESTTRANSACTION_H
#define HACKATON_WALLET_TESTTRANSACTION_H


#include <QtCore/QObject>
#include <QtTest/QTest>
#include "../api.h"

class TestTransaction : public QObject {
Q_OBJECT
public:
    TestTransaction(QObject *parent = nullptr);

private slots:

    void prepareTransaction();

    void signTransaction();

private:
    Api *_api;
};


#endif //HACKATON_WALLET_TESTTRANSACTION_H
