#include "paymentFactory.h"
#include "paypalPaymentStrategy.h"
#include "StripePaymentStrategy.h"
#include "SquarePaymentStrategy.h"

PaymentStrategy *PaymentFactory::getPaymentService(PaymentService service)
{
    if (service == PaymentService::paypal)
        return new PayPalPaymentStrategy;
    else if (service == PaymentService::stripe)
        return new StripePaymentStrategy;
    else if (service == PaymentService::square)
        return new SquarePaymentStrategy;
}