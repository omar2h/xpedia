#include "reservationFactory.h"
#include "../../model/flightReservation.h"

Reservation *ReservationFactory::getReservation(RequestType type)
{
    if (type == RequestType::flight)
        return new FlightReservation;
}
