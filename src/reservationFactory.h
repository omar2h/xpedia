#ifndef __RESERVATIONFACTORY_H__
#define __RESERVATIONFACTORY_H__
#include "reservation.h"
enum class RequestType;

class ReservationFactory
{
public:
    static Reservation *getRequest(RequestType);
};
#endif // __RESERVATIONFACTORY_H__