//
// Created by Artem Antonov on 03.12.17.
//

#include <QDebug>

#include "Signer.h"
#include <secp256k1.h>
#include <secp256k1_recovery.h>

#define RECOVERY_PARAM_COMPRESSED 4
#define RECOVERY_PARAM_COMPACT 27

QByteArray Signer::sign(QByteArray key, QByteArray transaction) {
    const secp256k1_context *context = secp256k1_context_create(SECP256K1_CONTEXT_SIGN | SECP256K1_CONTEXT_VERIFY);
    auto *_signature = new secp256k1_ecdsa_recoverable_signature();
    auto *serializedSignature = new unsigned char[64];
    int recoveryId;
    int ndata[1];
    ndata[0] = 0;

    while (true) {
        ndata[0] += 1;
        secp256k1_ecdsa_sign_recoverable(context, _signature, (const unsigned char *) transaction.constData(),
                                         (const unsigned char *) key.constData(), NULL, ndata);

        qDebug() << "Signature: " << QByteArray((char *) _signature->data).toHex();

        secp256k1_ecdsa_recoverable_signature_serialize_compact(context, serializedSignature, &recoveryId, _signature);

        if (
                !(serializedSignature[0] & 0x80) &&
                !((serializedSignature[0] == 0) && !(serializedSignature[1] && 0x80)) &&
                !(serializedSignature[32] & 0x80) &&
                !((serializedSignature[32] == 0) && !(serializedSignature[33] && 0x80))
                ) {
            break;
        }
    }

    qDebug() << "Recovery ID: " << recoveryId;

    auto cRecoveryId = QString::number(recoveryId + RECOVERY_PARAM_COMPRESSED + RECOVERY_PARAM_COMPACT, 16);

    qDebug() << "Signature serialized: " << QByteArray((char *) serializedSignature).toHex();

    return QByteArray::fromHex(cRecoveryId.toUtf8()).append((char *) serializedSignature);
}

bool Signer::verify(QByteArray signature, QByteArray message) {
    const secp256k1_context *context = secp256k1_context_create(SECP256K1_CONTEXT_VERIFY);

    auto *_signature = new secp256k1_ecdsa_recoverable_signature();
    auto *_normalSignature = new secp256k1_ecdsa_signature();

    auto *_publicKey = new secp256k1_pubkey();

    memcpy((char *) _signature->data, signature.mid(1).constData(), 65);

    if (!secp256k1_ecdsa_recover(context, _publicKey, _signature, (unsigned char *) message.data())) {
        return false;
    };

    if (!secp256k1_ecdsa_recoverable_signature_convert(context, _normalSignature, _signature)) {
        return false;
    };

    return (bool) secp256k1_ecdsa_verify(context, _normalSignature, (unsigned char *) message.data(), _publicKey);
}

bool Signer::verifySecret(QByteArray secret) {
    const secp256k1_context *context = secp256k1_context_create(SECP256K1_CONTEXT_VERIFY);

    return static_cast<bool>(secp256k1_ec_seckey_verify(context, (unsigned char *) secret.data()));
}

QByteArray Signer::getPublicFromSecret(QByteArray secret) {
    const secp256k1_context *context = secp256k1_context_create(SECP256K1_CONTEXT_SIGN);
    secp256k1_pubkey pubkey;

    secp256k1_ec_pubkey_create(context, &pubkey, (unsigned char *) secret.data());

    return QByteArray((char *) pubkey.data);
}

QByteArray Signer::getPublicFromSign(QByteArray signature, QByteArray message) {
    const secp256k1_context *context = secp256k1_context_create(SECP256K1_CONTEXT_VERIFY);

    secp256k1_pubkey pubkey;

    auto *_signature = new secp256k1_ecdsa_recoverable_signature();
    memcpy((char *) _signature->data, signature.constData(), 65);

    const auto isRecover = static_cast<const bool>(secp256k1_ecdsa_recover(context, &pubkey, _signature,
                                                                           (unsigned char *) message.data()));

    return QByteArray((char *) pubkey.data);
}
