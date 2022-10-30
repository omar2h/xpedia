#ifndef __ITINERARYITEM_H__
#define __ITINERARYITEM_H__
#include <string>
enum class ReservationType;
enum class RequestType;
class ItineraryItem
{
    ReservationType type;
    RequestType reqType;

public:
    virtual std::string toString() const = 0;
    virtual ItineraryItem *Clone() = 0;
    virtual ~ItineraryItem() = default;

    virtual ReservationType getType() const;
    virtual void setType(const ReservationType &);

    RequestType getReqType() const;
    void setReqType(const RequestType &reqType_);
};
#endif // __ITINERARYITEM_H__