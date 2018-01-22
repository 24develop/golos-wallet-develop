//
// Created by Artem Antonov on 28.11.17.
//

#include <QtTest>

#include "TestAuth.h"
#include "../lib/Auth.h"

void TestAuth::toWif() {
    auto wifKey = Auth::toWif("user", "password", "role");

    QCOMPARE(wifKey, QString("5JYdb8nw8rmNEABvJTKGounQ6y87MeWauodq17q43tXFFNn57c5"));
}

void TestAuth::fromWif() {
    auto privateKey = Auth::fromWif("5JYdb8nw8rmNEABvJTKGounQ6y87MeWauodq17q43tXFFNn57c5");

    QCOMPARE(privateKey, QByteArray::fromHex("6026403e18fb4ea6fe83800ccc74f37413a87e04c36794bea64d9da7f7255ae0"));
}
