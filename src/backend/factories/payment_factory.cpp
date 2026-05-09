#include "payment_factory.hpp"
#include "../payments/paypal_payment_strategy.hpp"
#include "../payments/stripe_payment_strategy.hpp"
#include "../payments/square_payment_strategy.hpp"

PaymentStrategy *PaymentFactory::getPaymentService(PaymentService service)
{
    if (service == PaymentService::paypal)
        return new PayPalPaymentStrategy;
    else if (service == PaymentService::stripe)
        return new StripePaymentStrategy;
    else if (service == PaymentService::square)
        return new SquarePaymentStrategy;
}
