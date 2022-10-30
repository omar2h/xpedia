#ifndef __PAYPALPAYMENTSTRATEGY_H__
#define __PAYPALPAYMENTSTRATEGY_H__
#include "../APIs/expedia_payments_api.h"
#include "paymentStrategy.h"
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
#endif // __PAYPALPAYMENTSTRATEGY_H__