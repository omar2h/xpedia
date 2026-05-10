#include "reservation_request_factory.hpp"
#include "../requests/flight_request.hpp"
#include "../requests/hotel_request.hpp"

std::unique_ptr<ReservationRequest> ReservationRequestFactory::getRequest(RequestType type)
{
    if (type == RequestType::flight)
        return std::make_unique<FlightRequest>();
    else if (type == RequestType::hotel)
        return std::make_unique<HotelRequest>();
    return nullptr;
}
