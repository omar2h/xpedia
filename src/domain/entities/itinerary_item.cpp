#include "itinerary_item.hpp"
#include "reservation.hpp"

ReservationType ItineraryItem::getType() const { return type; }
void ItineraryItem::setType(const ReservationType &type_) { type = type_; }
RequestType ItineraryItem::getRequestType() const
{
    return requestType;
}

void ItineraryItem::setRequestType(const RequestType &requestType_)
{
    requestType = requestType_;
}
