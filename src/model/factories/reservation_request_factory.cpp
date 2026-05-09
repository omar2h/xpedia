#include "reservation_request_factory.hpp"
#include "../requests/flight_request.hpp"
#include "../requests/hotel_request.hpp"

ReservationRequest *ReservationRequestFactory::getRequest(RequestType type)
{
    if (type == RequestType::flight)
        return new FlightRequest;
    else if (type == RequestType::hotel)
        return new HotelRequest;
}
