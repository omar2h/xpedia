#include "reservation.h"
#include "itineraryItem.h"

void Reservation::setType(ItineraryItem const *item)
{
    type = item->getType();
}

void Reservation::setReqType(ItineraryItem const *item)
{
    reqType = item->getReqType();
}