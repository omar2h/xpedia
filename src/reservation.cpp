#include "reservation.h"
#include "itineraryItem.h"

void Reservation::setType(ItineraryItem const *item)
{
    type = item->getType();
}