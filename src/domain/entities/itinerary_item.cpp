#include "itinerary_item.hpp"

RequestType ItineraryItem::getRequestType() const
{
    return requestType;
}

void ItineraryItem::setRequestType(const RequestType& requestType_)
{
    requestType = requestType_;
}
