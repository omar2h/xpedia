#pragma once

#include <string>
#include <memory>

enum class ReservationType;
enum class RequestType;
class ItineraryItem
{
    ReservationType type;
    RequestType reqType;

public:
    virtual std::string toString() const = 0;
    virtual std::unique_ptr<ItineraryItem> clone() const = 0;
    virtual ~ItineraryItem() = default;

    virtual ReservationType getType() const;
    virtual void setType(const ReservationType &);

    RequestType getReqType() const;
    void setReqType(const RequestType &reqType_);
};
