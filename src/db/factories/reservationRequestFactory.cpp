#include "reservationRequestFactory.h"
#include "../../model/flightRequest.h"

ReservationRequest *ReservationRequestFactory::getRequest(RequestType type)
{
    if (type == RequestType::flight)
        return new FlightRequest;
    return {};
}
