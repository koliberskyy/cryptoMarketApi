#ifndef ABSTRACTMARKET_H
#define ABSTRACTMARKET_H

#include "AbstractRequests/abstractrequests.h"
#include <list>

using string_type = QString;

struct MarketRequestMethods
{
    string_type getTickers;
};


struct MarketRequestParams{
    explicit MarketRequestParams(){}
    MarketRequestParams(
            string_type &&__host,
            MarketRequestMethods &&__methods):
    host{__host},
    methods{__methods}
    {}

    string_type host;
    MarketRequestMethods methods;
};

/*
 *  Набор интерфесов для работы с api криптовалютных бирж
*/
class AbstractMarket : public AbstractRequests
{
    Q_OBJECT

public:
    explicit AbstractMarket(std::unique_ptr<MarketRequestParams> __params, std::shared_ptr<QNetworkAccessManager> __netManager = nullptr, QObject *parent = nullptr): AbstractRequests(__netManager, parent), params{std::make_unique<MarketRequestParams>()}
    {
        params.swap(__params);
    }

    template<typename STR_T>
    void getSymbolList(STR_T query)
    {
        sendGet(params->host, params->methods.getTickers, std::forward<STR_T>(query));
    }

signals:
    void tickersRecived(std::list<QString> tickerList);

protected:

    virtual void parceNetworkReply(QNetworkRequest &&request, QNetworkReply::NetworkError &&error, QByteArray &&reply) final
    {
        if(error == QNetworkReply::NoError){
            auto info = request.url().path();

            if(info == params->methods.getTickers){
                emit tickersRecived(parceSymbolListReply(std::move(reply)));
            }
        }
    }

    virtual std::list<QString> parceSymbolListReply(QByteArray &&reply) = 0;

private:
    std::unique_ptr<MarketRequestParams> params;


};

#endif // ABSTRACTMARKET_H
