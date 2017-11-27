//
// Created by artem on 25.11.17.
//

#ifndef HACKATON_WALLET_TESTCOMMAND_H
#define HACKATON_WALLET_TESTCOMMAND_H

#include "../command.h"

#include <QtTest/QtTest>
#include <QStringList>

class TestCommand : public QObject {
Q_OBJECT

private slots:

    void toJson();

    void toJsonArray();

    void toString();

    void toStringArray();
};


#endif //HACKATON_WALLET_TESTCOMMAND_H
