#pragma once

#include "payment_strategy.hpp"
#include "../../apis/expedia_payments_api.hpp"
#include "../../include/json.hpp"
#include <sstream>
using json = nlohmann::json;

class SquarePaymentStrategy : public PaymentStrategy
{

public:
    string getJsonQuery(const PaymentCard &card, double amount)
    {
        json obj;
        obj["user_info"] = json::array({card.getOwner(), "cairo"});
        obj["card_info"]["ID"] = "1";
        obj["card_info"]["DATE"] = card.getExpiryDate();
        obj["card_info"]["CCV"] = card.getCcv();
        obj["money"] = amount;
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
