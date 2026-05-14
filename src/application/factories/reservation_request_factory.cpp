#include "reservation_request_factory.hpp"
#include "../../domain/requests/flight_request.hpp"
#include "../../domain/requests/hotel_request.hpp"

std::unique_ptr<ReservationRequest> ReservationRequestFactory::getRequest(RequestType type)
{
    if (type == RequestType::flight)
        return std::make_unique<FlightRequest>();
    if (type == RequestType::hotel)
        return std::make_unique<HotelRequest>();
    return nullptr;
}
