#include "reservation.hpp"
#include "itinerary_item.hpp"

void Reservation::setType(ItineraryItem const *item)
{
    type = item->getType();
}

void Reservation::setReqType(ItineraryItem const *item)
{
    reqType = item->getReqType();
}