#include "payment_factory.h"
#include "../payments/paypal_payment_strategy.h"
#include "../payments/stripe_payment_strategy.h"
#include "../payments/square_payment_strategy.h"

PaymentStrategy *PaymentFactory::getPaymentService(PaymentService service)
{
    if (service == PaymentService::paypal)
        return new PayPalPaymentStrategy;
    else if (service == PaymentService::stripe)
        return new StripePaymentStrategy;
    else if (service == PaymentService::square)
        return new SquarePaymentStrategy;
}
