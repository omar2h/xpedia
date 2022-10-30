#include "reservationFactory.h"
#include "../../model/flightReservation.h"
#include "../../model/hotelReservation.h"

Reservation *ReservationFactory::getReservation(RequestType type)
{
    if (type == RequestType::flight)
        return new FlightReservation;
    else if (type == RequestType::hotel)
        return new HotelReservation;
}
