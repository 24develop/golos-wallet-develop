//
// Created by Artem Antonov on 03.12.17.
//

#include <QDebug>

#include "TestSigner.h"

void TestSigner::sign() {
    auto signature = Signer::sign(
            QByteArray::fromHex("75c49490ba220582e208f3559438f0379c9bd17754362bb2bafe633669980575"),
            //QByteArray::fromHex("6026403e18fb4ea6fe83800ccc74f37413a87e04c36794bea64d9da7f7255ae0"),
            //QByteArray::fromHex("1020eb4e44c84c91a3119a91145d04decf77be6c200929749ecbe27bc6d54c7e")
            QByteArray::fromHex("6026403e18fb4ea6fe83800ccc74f37413a87e04c36794bea64d9da7f7255ae0")
    );

    qDebug() << "Verified: " << Signer::verify(
            signature,
            QByteArray::fromHex("6026403e18fb4ea6fe83800ccc74f37413a87e04c36794bea64d9da7f7255ae0")
    );

    qDebug() << "Signature: " << signature.toHex();
}

void TestSigner::verify() {
    auto message = QByteArray::fromHex("1020eb4e44c84c91a3119a91145d04decf77be6c200929749ecbe27bc6d54c7e");
    auto key = QByteArray::fromHex("6026403e18fb4ea6fe83800ccc74f37413a87e04c36794bea64d9da7f7255ae0");

    auto signature = Signer::sign(key, message);

    auto verified = Signer::verify(signature, message);

    qDebug() << "Verified: " << verified;
}
