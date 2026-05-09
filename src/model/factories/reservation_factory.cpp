#include "reservation_factory.hpp"
#include "../reservations/flight_reservation.hpp"
#include "../reservations/hotel_reservation.hpp"

Reservation *ReservationFactory::getReservation(RequestType type)
{
    if (type == RequestType::flight)
        return new FlightReservation;
    else if (type == RequestType::hotel)
        return new HotelReservation;
}
