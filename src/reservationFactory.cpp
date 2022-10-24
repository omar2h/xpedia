#include "reservationFactory.h"
#include "flightReservation.h"

Reservation *ReservationFactory::getRequest(RequestType type)
{
    if (type == RequestType::flight)
        return new FlightReservation;
}
