//
// Created by artem on 28.11.17.
//

#ifndef HACKATON_WALLET_QBS58_H
#define HACKATON_WALLET_QBS58_H

#include <QtCore/QString>
#include "libbase58.h"

class QBS58 {
public:
    static QString encode(QByteArray raw);
};


#endif //HACKATON_WALLET_QBS58_H
