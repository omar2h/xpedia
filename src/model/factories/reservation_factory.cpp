#include "reservation_factory.h"
#include "../reservations/flight_reservation.h"
#include "../reservations/hotel_reservation.h"

Reservation *ReservationFactory::getReservation(RequestType type)
{
    if (type == RequestType::flight)
        return new FlightReservation;
    else if (type == RequestType::hotel)
        return new HotelReservation;
}
