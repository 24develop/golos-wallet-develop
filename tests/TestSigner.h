//
// Created by artem on 03.12.17.
//

#ifndef HACKATON_WALLET_TESTSIGNER_H
#define HACKATON_WALLET_TESTSIGNER_H

#include <QtCore/QObject>
#include <QtTest/QTest>

#include "../lib/Signer.h"

class TestSigner : public QObject {
Q_OBJECT

private slots:

    void sign();

    void verify();
};


#endif //HACKATON_WALLET_TESTSIGNER_H
