#ifndef __STRIPEPAYMENTSTRATEGY_H__
#define __STRIPEPAYMENTSTRATEGY_H__
#include "paymentStrategy.h"
#include "../APIs/expedia_payments_api.h"

class StripePaymentStrategy : public PaymentStrategy
{
    StripeUserInfo userInfo;
    StripeCardInfo cardInfo;
    StripePaymentAPI stripeAPI;

public:
    bool pay(const PaymentCard &card, double amount)
    {
        userInfo.name = card.getOwner();
        userInfo.address = "cairo";
        cardInfo.id = "1";
        cardInfo.expiry_date = card.getExpiryDate();
        return StripePaymentAPI::WithDrawMoney(userInfo, cardInfo, amount);
    }

    ~StripePaymentStrategy() override = default;
};
#endif // __STRIPEPAYMENTSTRATEGY_H__