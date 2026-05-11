#pragma once

#include "../../apis/expedia_payments_api.hpp"
#include "../../application/payments/payment_strategy.hpp"
class PayPalPaymentStrategy : public PaymentStrategy
{
    PayPalCreditCard paypalCard;
    PayPalOnlinePaymentAPI paypalApi{};

public:
    bool pay(const PaymentCard &card, double amount)
    {
        paypalCard.id = "1";
        paypalCard.name = card.getOwner();
        paypalCard.address = "cairo";
        paypalCard.expiry_date = card.getExpiryDate();
        paypalCard.ccv = stoi(card.getCcv());

        paypalApi.SetCardInfo(&paypalCard);
        return paypalApi.MakePayment(amount);
    }

    ~PayPalPaymentStrategy() override = default;
};
