//
// Created by Artem Antonov on 28.11.17.
//

#include <QDebug>

#include "QBS58.h"

#define RESULT_SIZE 256

QString QBS58::encode(QByteArray raw) {
    auto encoded = new char[RESULT_SIZE];
    const char *rawArray = raw.constData();

    auto encodedSize = (size_t) RESULT_SIZE;
    auto rawSize = (size_t) raw.length();

    b58enc(encoded, &encodedSize, (const void *) rawArray, rawSize);

    return QString(encoded);
}

QByteArray QBS58::decode(QString wif) {
    char rawArray[RESULT_SIZE];

    auto rawSize = (size_t) RESULT_SIZE;
    auto encodedSize = (size_t) wif.length();

    b58tobin(&rawArray, &rawSize, wif.toUtf8().constData(), encodedSize);

    auto *arr = new char[rawSize];

    strncpy(arr, rawArray + (RESULT_SIZE - (int) rawSize), rawSize);

    return QByteArray(arr);
}
