#include <QCoreApplication>
#include <QTest>

#include "TestCommand.h"
#include "TestResponse.h"
#include "TestQBS58.h"
#include "TestAuth.h"

int main(int argc, char *argv[]) {
    int status = 0;

    TestCommand testCommand;
    TestResponse testResponse;
    TestQBS58 testQBS58;
    TestAuth testAuth;

    QStringList arguments = QCoreApplication::arguments();

    status |= QTest::qExec(&testCommand, arguments);
    status |= QTest::qExec(&testResponse, arguments);
    status |= QTest::qExec(&testQBS58, arguments);
    status |= QTest::qExec(&testAuth, arguments);

    return status;
}