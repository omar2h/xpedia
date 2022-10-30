#include "reservationRequestFactory.h"
#include "../../model/flightRequest.h"
#include "../../model/hotelRequest.h"

ReservationRequest *ReservationRequestFactory::getRequest(RequestType type)
{
    if (type == RequestType::flight)
        return new FlightRequest;
    else if (type == RequestType::hotel)
        return new HotelRequest;
}