#include "reservationRequestFactory.h"
#include "flightRequest.h"

ReservationRequest *ReservationRequestFactory::getRequest(RequestType type)
{
    if (type == RequestType::flight)
        return new FlightRequest;
}