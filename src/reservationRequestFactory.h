#ifndef __RESERVATIONREQUESTFACTORY_H__
#define __RESERVATIONREQUESTFACTORY_H__
#include "reservationRequest.h"

class ReservationRequestFactory
{
public:
    static ReservationRequest *getRequest(RequestType);
};
#endif // __RESERVATIONREQUESTFACTORY_H__