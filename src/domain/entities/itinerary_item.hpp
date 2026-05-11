#pragma once

#include <string>
#include <memory>

#include "../request_type.hpp"

enum class ReservationType;
class ItineraryItem
{
    ReservationType type;
    RequestType requestType;

public:
    [[nodiscard]] virtual std::string toString() const = 0;
    [[nodiscard]] virtual std::unique_ptr<ItineraryItem> clone() const = 0;
    virtual ~ItineraryItem() = default;

    virtual ReservationType getType() const;
    virtual void setType(const ReservationType &);

    RequestType getRequestType() const;
    void setRequestType(const RequestType &requestType_);
};
