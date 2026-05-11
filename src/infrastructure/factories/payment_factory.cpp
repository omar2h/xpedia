#include "payment_factory.hpp"
#include "../../exception.hpp"
#include "payments/paypal_payment_strategy.hpp"
#include "payments/stripe_payment_strategy.hpp"
#include "payments/square_payment_strategy.hpp"

std::unique_ptr<PaymentStrategy> PaymentFactory::getPaymentService(PaymentService service) const
{
    switch (service)
    {
    case PaymentService::paypal:
        return std::make_unique<PayPalPaymentStrategy>();
    case PaymentService::stripe:
        return std::make_unique<StripePaymentStrategy>();
    case PaymentService::square:
        return std::make_unique<SquarePaymentStrategy>();
    }
    throw ValidationException("Unknown payment service");
}
