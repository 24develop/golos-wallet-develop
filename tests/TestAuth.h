//
// Created by artem on 28.11.17.
//

#ifndef HACKATON_WALLET_TESTAUTH_H
#define HACKATON_WALLET_TESTAUTH_H


#include <QtCore/QObject>

class TestAuth : public QObject {
Q_OBJECT

private slots:

    void toWif();
};


#endif //HACKATON_WALLET_TESTAUTH_H
