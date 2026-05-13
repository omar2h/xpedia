#pragma once

#include "../../domain/entities/payment_card.hpp"
enum class PaymentService
{
    paypal,
    stripe,
    square
};

class PaymentStrategy
{
public:
    [[nodiscard]] virtual bool pay(const PaymentCard &, double) = 0;
    virtual ~PaymentStrategy() = default;
};
