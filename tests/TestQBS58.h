//
// Created by Artem Antonov on 28.11.17.
//

#ifndef HACKATON_WALLET_TESTQBS58_H
#define HACKATON_WALLET_TESTQBS58_H


#include <QtCore/QObject>

class TestQBS58 : public QObject {
Q_OBJECT

private slots:

    void encode();

    void decode();
};


#endif //HACKATON_WALLET_TESTQBS58_H
