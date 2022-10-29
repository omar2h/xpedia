#include "paymentFactory.h"
#include "../../backend/paypalPaymentStrategy.h"
#include "../../backend/StripePaymentStrategy.h"
#include "../../backend/SquarePaymentStrategy.h"

PaymentStrategy *PaymentFactory::getPaymentService(PaymentService service)
{
    if (service == PaymentService::paypal)
        return new PayPalPaymentStrategy;
    else if (service == PaymentService::stripe)
        return new StripePaymentStrategy;
    else if (service == PaymentService::square)
        return new SquarePaymentStrategy;
}