#include "itineraryItem.h"
#include "reservation.h"

ReservationType ItineraryItem::getType() const { return type; }
void ItineraryItem::setType(const ReservationType &type_) { type = type_; }
RequestType ItineraryItem::getReqType() const
{
    return reqType;
}

void ItineraryItem::setReqType(const RequestType &reqType_)
{
    reqType = reqType_;
}
