//
// Created by artem on 03.12.17.
//

#include <QDebug>

#include "TestSigner.h"

void TestSigner::sign() {
    auto signature = Signer::sign(
            QByteArray::fromHex("6026403e18fb4ea6fe83800ccc74f37413a87e04c36794bea64d9da7f7255ae0"),
            QByteArray::fromHex("1020eb4e44c84c91a3119a91145d04decf77be6c200929749ecbe27bc6d54c7e")
    );

    qDebug() << "Signature: " << signature.toHex();
}

void TestSigner::verify() {

}
