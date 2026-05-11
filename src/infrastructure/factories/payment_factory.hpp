#pragma once

#include "../../application/payments/payment_strategy.hpp"
#include <memory>

class PaymentFactory
{
public:
    [[nodiscard]] std::unique_ptr<PaymentStrategy> getPaymentService(PaymentService service) const;
};
