#include "reservation_factory.hpp"
#include "../entities/flight_reservation.hpp"
#include "../entities/hotel_reservation.hpp"

std::unique_ptr<Reservation> ReservationFactory::getReservation(RequestType type)
{
    if (type == RequestType::flight)
    {
        auto reservation = std::make_unique<FlightReservation>();
        reservation->setRequestType(type);
        reservation->setCategory(ReservationCategory::flight);
        return reservation;
    }

    if (type == RequestType::hotel)
    {
        auto reservation = std::make_unique<HotelReservation>();
        reservation->setRequestType(type);
        reservation->setCategory(ReservationCategory::hotel);
        return reservation;
    }

    return nullptr;
}
