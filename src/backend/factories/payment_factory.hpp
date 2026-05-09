#pragma once

#include "../payments/payment_strategy.hpp"
#include <string>

class PaymentFactory
{
public:
    static PaymentStrategy *getPaymentService(PaymentService);
};
