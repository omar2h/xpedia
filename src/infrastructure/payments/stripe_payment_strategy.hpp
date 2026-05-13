#pragma once

#include "../../application/payments/payment_strategy.hpp"
#include "../../apis/expedia_payments_api.hpp"

class StripePaymentStrategy : public PaymentStrategy
{
    StripeUserInfo userInfo;
    StripeCardInfo cardInfo;
    StripePaymentAPI stripeAPI;

public:
    [[nodiscard]] bool pay(const PaymentCard &card, double amount)
    {
        userInfo.name = card.getOwner();
        userInfo.address = "cairo";
        cardInfo.id = "1";
        cardInfo.expiry_date = card.getExpiryDate();
        return StripePaymentAPI::WithDrawMoney(userInfo, cardInfo, amount);
    }

    ~StripePaymentStrategy() override = default;
};
