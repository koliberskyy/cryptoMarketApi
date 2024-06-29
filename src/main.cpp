#include <iostream>
#include <QJsonDocument>
#include <QCoreApplication>
#include "bybitapi.h"
class MarketApiTest : public BybitApi{



public:
    MarketApiTest() : BybitApi(std::make_shared<QNetworkAccessManager>())
    {
    }




public:
    void test()
    {
        getSymbolList("category=spot");
    }
};


int main(int argc, char *argv[]){

    QCoreApplication a(argc, argv);
    MarketApiTest reqTest;
    reqTest.test();
    return a.exec();
}
