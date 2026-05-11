#pragma once

#include "../../model/payment_card.hpp"
enum class PaymentService
{
    paypal,
    stripe,
    square
};

class PaymentStrategy
{
public:
    virtual bool pay(const PaymentCard &, double) = 0;
    virtual ~PaymentStrategy() = default;
};
