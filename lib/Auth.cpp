//
// Created by artem on 28.11.17.
//

#include <QtCore/QCryptographicHash>
#include <QDebug>

#include "Auth.h"
#include "bs58/QBS58.h"

QString Auth::toWif(QString name, QString password, QString role) {
    QString seed = name + password + role;

    auto hash = QCryptographicHash::hash(seed.toUtf8(), QCryptographicHash::Sha256);

    QByteArray privateKey;
    privateKey.append((char) 0x80).append(hash);

    auto checksum = QCryptographicHash::hash(privateKey, QCryptographicHash::Sha256);
    checksum = QCryptographicHash::hash(checksum, QCryptographicHash::Sha256);
    checksum = checksum.mid(0, 4);

    qDebug() << "Checksum: " << checksum.toHex();

    QByteArray privateWif;

    privateWif.append(privateKey);

    qDebug() << "Private key:" << privateKey.toHex();

    privateWif.append(checksum);

    qDebug() << "Private wif: " << privateWif.toHex();

    return QBS58::encode(privateWif);
}
