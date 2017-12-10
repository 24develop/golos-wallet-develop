//
// Created by artem on 03.12.17.
//

#include <QDebug>

#include "Signer.h"
#include <secp256k1.h>
#include <secp256k1_recovery.h>

#define RECOVERY_PARAM_COMPRESSED 4
#define RECOVERY_PARAM_COMPACT 27

QByteArray Signer::sign(QByteArray key, QByteArray transaction) {
    const secp256k1_context *context = secp256k1_context_create(SECP256K1_CONTEXT_SIGN);
    auto *_signature = new secp256k1_ecdsa_recoverable_signature();

    secp256k1_ecdsa_sign_recoverable(context, _signature, (const unsigned char *) transaction.constData(),
                                     (const unsigned char *) key.constData(), NULL, NULL);

    qDebug() << "Signature: " << QByteArray((char *) _signature->data).toHex();

    auto *serializedSignature = new unsigned char[64];
    int recoveryId;

    secp256k1_ecdsa_recoverable_signature_serialize_compact(context, serializedSignature, &recoveryId, _signature);

    qDebug() << "Recovery ID: " << recoveryId;

    auto cRecoveryId = QString::number(recoveryId + RECOVERY_PARAM_COMPRESSED + RECOVERY_PARAM_COMPACT, 16);

    qDebug() << "Signature serialized: " << QByteArray((char *) serializedSignature).toHex();

    return QByteArray::fromHex(cRecoveryId.toUtf8()).append((char *) serializedSignature);
}

bool Signer::verify(QByteArray signature) {
    return false;
}
