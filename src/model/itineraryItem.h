#ifndef __ITINERARYITEM_H__
#define __ITINERARYITEM_H__
#include <string>
#include <iostream>

enum class ReservationType;
enum class RequestType;
class ItineraryItem
{
    ReservationType type;
    RequestType reqType;

public:
    virtual std::string toString() const = 0;
    virtual ItineraryItem *Clone() = 0;
    virtual ~ItineraryItem()
    {
        std::cout << "ItineraryItem destructor\n";
    }

    virtual ReservationType getType() const;
    virtual void setType(const ReservationType &);

    RequestType getReqType() const;
    void setReqType(const RequestType &reqType_);
};
#endif // __ITINERARYITEM_H__