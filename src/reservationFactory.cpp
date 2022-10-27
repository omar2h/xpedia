#include "reservationFactory.h"
#include "flightReservation.h"

Reservation *ReservationFactory::getReservation(RequestType type)
{
    if (type == RequestType::flight)
        return new FlightReservation;
}
