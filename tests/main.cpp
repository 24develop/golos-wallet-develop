#include <QCoreApplication>
#include <QTest>

#include "TestCommand.h"
#include "TestResponse.h"

int main(int argc, char *argv[]) {
    int status = 0;

    TestCommand testCommand;
    TestResponse testResponse;

    QStringList arguments = QCoreApplication::arguments();

    status |= QTest::qExec(&testCommand, arguments);
    status |= QTest::qExec(&testResponse, arguments);

    return status;
}