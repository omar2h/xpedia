#pragma once

#include "../../application/payments/payment_strategy.hpp"
#include "../../infrastructure/json_keys.hpp"
#include "../../apis/expedia_payments_api.hpp"
#include "../../third_party/json.hpp"
#include <sstream>
using json = nlohmann::json;

class SquarePaymentStrategy : public PaymentStrategy
{

public:
    string getJsonQuery(const PaymentCard &card, double amount)
    {
        json obj;
        obj[JsonKeys::userInfo] = json::array({card.getOwner(), "cairo"});
        obj[JsonKeys::cardInfo][JsonKeys::paymentId] = "1";
        obj[JsonKeys::cardInfo][JsonKeys::paymentDate] = card.getExpiryDate();
        obj[JsonKeys::cardInfo][JsonKeys::paymentCcv] = card.getCcv();
        obj[JsonKeys::paymentMoney] = amount;
        std::ostringstream oss;
        oss << obj;
        return oss.str();
    }
    bool pay(const PaymentCard &card, double amount)
    {
        return SquarePaymentAPI::WithDrawMoney(getJsonQuery(card, amount));
    }

    ~SquarePaymentStrategy() override = default;
};
