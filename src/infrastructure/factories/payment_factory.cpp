#include "payment_factory.hpp"
#include "payments/paypal_payment_strategy.hpp"
#include "payments/stripe_payment_strategy.hpp"
#include "payments/square_payment_strategy.hpp"

std::unique_ptr<PaymentStrategy> PaymentFactory::getPaymentService(PaymentService service)
{
    if (service == PaymentService::paypal)
        return std::make_unique<PayPalPaymentStrategy>();
    else if (service == PaymentService::stripe)
        return std::make_unique<StripePaymentStrategy>();
    else if (service == PaymentService::square)
        return std::make_unique<SquarePaymentStrategy>();
}
