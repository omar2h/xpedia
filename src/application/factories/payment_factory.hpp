#pragma once

#include <memory>
#include "../payments/payment_strategy.hpp"

class IPaymentFactory
{
public:
    [[nodiscard]] virtual std::unique_ptr<PaymentStrategy> getPaymentService(PaymentService service) const = 0;

    virtual ~IPaymentFactory() = default;
};
