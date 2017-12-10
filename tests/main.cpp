#include <QCoreApplication>
#include <QTest>

#include "TestCommand.h"
#include "TestResponse.h"
#include "TestQBS58.h"
#include "TestAuth.h"
#include "TestTransaction.h"
#include "TestSigner.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    int status = 0;

    TestCommand testCommand;
    TestResponse testResponse;
    TestQBS58 testQBS58;
    TestAuth testAuth;
    TestTransaction testTransaction;
    TestSigner testSigner;

    QStringList arguments = QCoreApplication::arguments();

    /*
    status |= QTest::qExec(&testCommand, arguments);
    status |= QTest::qExec(&testResponse, arguments);
    status |= QTest::qExec(&testQBS58, arguments);
    status |= QTest::qExec(&testAuth, arguments);
    status |= QTest::qExec(&testTransaction, arguments);
     */
    status |= QTest::qExec(&testSigner, arguments);

    return status;
}