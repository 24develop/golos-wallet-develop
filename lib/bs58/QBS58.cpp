//
// Created by artem on 28.11.17.
//

#include "QBS58.h"

#define RESULT_SIZE 256

QString QBS58::encode(QByteArray raw) {
    auto encoded = new char[RESULT_SIZE];
    const char *rawArray = raw.constData();

    size_t encodedSize = RESULT_SIZE;
    size_t rawSize = (size_t) raw.length();

    b58enc(encoded, &encodedSize, (const void *) rawArray, rawSize);

    return QString(encoded);
}
