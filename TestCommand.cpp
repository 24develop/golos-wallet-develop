//
// Created by artem on 25.11.17.
//

#include "TestCommand.h"

void TestCommand::toJson() {
    auto *args = new QStringList();

    args->append("arg1");
    args->append("arg2");

    Command *command = new Command(10, "test", args);

    QCOMPARE(command->toJSON(), QString("{\"id\":10,\"method\":\"test\",\"params\":[\"arg1\",\"arg2\"]}"));
}

void TestCommand::toString() {
    auto *args = new QStringList();

    args->append("arg1");
    args->append("arg2");

    Command *command = new Command(10, "test", args);

    QCOMPARE(command->toString(), QString("test arg1 arg2"));
}

QTEST_MAIN(TestCommand)

#include "TestCommand.moc"

