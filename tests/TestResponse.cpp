//
// Created by Artem Antonov on 26.11.17.
//

#include "TestResponse.h"
#include "../Response.h"

void TestResponse::constructor() {
    QString rawResponse = R"({"id": 10,"result":[1,2,3]})";

    auto response = new Response(rawResponse);

    QCOMPARE(response->getId(), 10);
    QCOMPARE(response->getResult().toArray().size(), 3);
}
