//
// Created by artem on 25.11.17.
//

#include "TestCommand.h"

void TestCommand::toJson() {
    auto args = new QJsonArray();

    args->append("arg1");
    args->append("arg2");

    Command *command = new Command(10, "test", args);

    QCOMPARE(command->toJSON(), QString("{\"id\":10,\"method\":\"test\",\"params\":[\"arg1\",\"arg2\"]}"));
}

void TestCommand::toJsonArray() {
    auto args = new QJsonArray();
    auto arrParam = QJsonArray {1, 2, 3};

    args->append(arrParam);

    Command *command = new Command(10, "test", args);

    QCOMPARE(command->toJSON(), QString("{\"id\":10,\"method\":\"test\",\"params\":[[1,2,3]]}"));
}

void TestCommand::toString() {
    auto args = new QJsonArray;

    args->append("arg1");
    args->append("arg2");

    Command *command = new Command(10, "test", args);

    QCOMPARE(command->toString(), QString("test arg1 arg2"));
}

void TestCommand::toStringArray() {
    auto args = new QJsonArray();
    auto arrParam = QJsonArray {1, 2, 3};

    args->append(arrParam);

    Command *command = new Command(10, "test", args);

    QCOMPARE(command->toString(), QString("test [1,2,3]"));
}

QTEST_MAIN(TestCommand)

#include "TestCommand.moc"

