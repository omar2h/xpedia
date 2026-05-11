#pragma once

#include "payments/payment_strategy.hpp"
#include <string>
#include <memory>

class PaymentFactory
{
public:
    static std::unique_ptr<PaymentStrategy> getPaymentService(PaymentService);
};
