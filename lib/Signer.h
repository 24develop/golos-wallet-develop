//
// Created by artem on 03.12.17.
//

#ifndef HACKATON_WALLET_SIGNER_H
#define HACKATON_WALLET_SIGNER_H


#include <QtCore/QByteArray>

class Signer {

public:
    static QByteArray sign(QByteArray key, QByteArray transaction);

    static bool verify(QByteArray signature);
};


#endif //HACKATON_WALLET_SIGNER_H
