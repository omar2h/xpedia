#ifndef __PAYMENTFACTORY_H__
#define __PAYMENTFACTORY_H__
#include "../payments/payment_strategy.h"
#include <string>

class PaymentFactory
{
public:
    static PaymentStrategy *getPaymentService(PaymentService);
};
#endif // __PAYMENTFACTORY_H__
