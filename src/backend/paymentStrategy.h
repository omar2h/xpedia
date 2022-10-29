#ifndef __PAYMENTSTRATEGY_H__
#define __PAYMENTSTRATEGY_H__
#include "../model/paymentCard.h"
enum class PaymentService
{
    paypal,
    stripe,
    square
};

class PaymentStrategy
{
public:
    virtual bool pay(const PaymentCard &, double) = 0;
    virtual ~PaymentStrategy() = default;
};
#endif // __PAYMENTSTRATEGY_H__