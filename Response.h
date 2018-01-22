//
// Created by Artem Antonov on 26.11.17.
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

    QJsonValue getResult() {
        return this->_result;
    }

    QJsonValue getError() {
        return this->_error;
    }
private:
    int _id;
    QJsonValue _result;
    QJsonValue _error;
};


#endif //HACKATON_WALLET_RESPONSE_H
