#include "reservation_factory.hpp"
#include "../entities/flight_reservation.hpp"
#include "../entities/hotel_reservation.hpp"

std::unique_ptr<Reservation> ReservationFactory::getReservation(RequestType type)
{
    if (type == RequestType::flight)
        return std::make_unique<FlightReservation>();
    if (type == RequestType::hotel)
        return std::make_unique<HotelReservation>();
    return nullptr;
}
