#ifndef __ITINERARYITEM_H__
#define __ITINERARYITEM_H__

#include <string>
class ItineraryItem
{
public:
    virtual std::string toString() const = 0;
    virtual ItineraryItem *Clone() = 0;
    virtual ~ItineraryItem() = default;
};
#endif // __ITINERARYITEM_H__