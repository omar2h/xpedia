#ifndef __ITINERARYITEM_H__
#define __ITINERARYITEM_H__
#include <string>
enum class ReservationType;
class ItineraryItem
{
    ReservationType type;

public:
    virtual std::string toString() const = 0;
    virtual ItineraryItem *Clone() = 0;
    virtual ~ItineraryItem() = default;

    virtual ReservationType getType() const;
    virtual void setType(const ReservationType &);
};
#endif // __ITINERARYITEM_H__