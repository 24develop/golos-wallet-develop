//
// Created by artem on 28.11.17.
//

#ifndef HACKATON_WALLET_AUTH_H
#define HACKATON_WALLET_AUTH_H


#include <QtCore/QString>

class Auth {
public:
    static QString toWif(QString name, QString password, QString role);

    static QByteArray fromWif(QString wif);
};


#endif //HACKATON_WALLET_AUTH_H
