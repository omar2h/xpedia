#include "itineraryItem.h"
#include "reservation.h"

ReservationType ItineraryItem::getType() const { return type; }
void ItineraryItem::setType(const ReservationType &type_) { type = type_; }