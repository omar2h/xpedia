#pragma once

#include "../../application/factories/payment_factory.hpp"
#include <string>
#include <memory>

class PaymentFactory : public IPaymentFactory
{
public:
    [[nodiscard]] std::unique_ptr<PaymentStrategy> getPaymentService(PaymentService service) const override;
};
