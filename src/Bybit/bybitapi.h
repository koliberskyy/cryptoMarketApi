#ifndef BYBITAPI_H
#define BYBITAPI_H

#include <abstractmarket.h>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <iostream>

struct BybitRequestParams : public MarketRequestParams{
    BybitRequestParams():
        MarketRequestParams
        (
            "api.bybit.com",
            MarketRequestMethods
            {
                "/v5/market/tickers"
            }
        ){}
};

/*
 * Класс-обертка над http api bybit.com
*/
class BybitApi : public AbstractMarket
{
    Q_OBJECT
public:
    explicit BybitApi(std::shared_ptr<QNetworkAccessManager> __netManger = nullptr, QObject *parent = nullptr):
        AbstractMarket(std::make_unique<BybitRequestParams>(), __netManger, parent)
    {
    }


protected:
    virtual std::list<QString> parceSymbolListReply(QByteArray &&reply) final
    {
        auto arr = QJsonDocument::fromJson(reply).object()["result"].toObject()["list"].toArray();
        std::list<QString> list;

        for(const auto &it : arr){
            auto a = it.toObject()["symbol"].toString();
            list.push_back(it.toObject()["symbol"].toString());
        }

        return std::move(list);
    }


};

#endif // BYBITAPI_H
