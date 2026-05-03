#include "reservation_request_factory.h"
#include "../requests/flight_request.h"
#include "../requests/hotel_request.h"

ReservationRequest *ReservationRequestFactory::getRequest(RequestType type)
{
    if (type == RequestType::flight)
        return new FlightRequest;
    else if (type == RequestType::hotel)
        return new HotelRequest;
}
