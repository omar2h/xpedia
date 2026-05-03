#ifndef __RESERVATIONREQUESTFACTORY_H__
#define __RESERVATIONREQUESTFACTORY_H__
#include "../requests/reservation_request.h"

class ReservationRequestFactory
{
public:
    static ReservationRequest *getRequest(RequestType);
};
#endif // __RESERVATIONREQUESTFACTORY_H__
