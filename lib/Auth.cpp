//
// Created by Artem Antonov on 28.11.17.
//

#include <QtCore/QCryptographicHash>
#include <QDebug>

#include "Auth.h"
#include "bs58/QBS58.h"

QString Auth::toWif(QString name, QString password, QString role) {
    QString seed = name + role + password;

    qDebug() << "Seed: " << seed;

    auto hash = QCryptographicHash::hash(seed.toUtf8(), QCryptographicHash::Sha256);

    qDebug() << "Seed hash: " << hash.toHex(' ');

    QByteArray privateKey;
    privateKey.append((char) 0x80).append(hash);

    auto checksum = QCryptographicHash::hash(privateKey, QCryptographicHash::Sha256);
    checksum = QCryptographicHash::hash(checksum, QCryptographicHash::Sha256);
    checksum = checksum.mid(0, 4);

    qDebug() << "Checksum: " << checksum.toHex(' ');

    QByteArray privateWif;

    privateWif.append(privateKey);

    qDebug() << "Private key:" << privateKey.toHex(' ');

    privateWif.append(checksum);

    qDebug() << "Private wif: " << privateWif.toHex(' ');

    auto wif = QBS58::encode(privateWif);

    qDebug() << "Wif key: " << wif;

    return wif;
}

QByteArray Auth::fromWif(QString wif) {
    qDebug() << "Wif: " << wif;

    auto privateWif = QBS58::decode(wif);
    auto privateKey = privateWif.left(privateWif.length() - 4);

    qDebug() << "Private wif: " << privateWif.toHex(' ');

    privateKey = privateKey.mid(1);

    qDebug() << "Private key: " << privateKey.toHex(' ');

    return privateKey;
}

QByteArray Auth::toBytes(QString wif) {
    return QBS58::decode(wif);
}
