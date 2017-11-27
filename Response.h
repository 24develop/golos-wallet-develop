//
// Created by artem on 26.11.17.
//

#ifndef HACKATON_WALLET_RESPONSE_H
#define HACKATON_WALLET_RESPONSE_H


#include <QtCore/QJsonArray>

class Response {
public:
    Response(QString rawResponse);

    int getId() {
        return this->_id;
    }

    QJsonArray getResult() {
        return this->_result;
    }

private:
    int _id;
    QJsonArray _result;
};


#endif //HACKATON_WALLET_RESPONSE_H
