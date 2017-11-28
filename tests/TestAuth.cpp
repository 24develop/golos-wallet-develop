//
// Created by artem on 28.11.17.
//

#include <QtTest>

#include "TestAuth.h"
#include "../lib/Auth.h"

void TestAuth::toWif() {
    auto wifKey = Auth::toWif("user", "password", "role");

    QCOMPARE(wifKey, QString("5KcC1oddVmdx2du1LNKqRS2S53RVYuvW5Ksv2NQAyNExhKwSbPb"));
}
