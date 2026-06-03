#pragma once

#include <memory>
#include <string>

#include "../request_type.hpp"
#include "reservation_category.hpp"

// Forward declaration of visitor
class ItineraryItemVisitor;

class ItineraryItem
{
    ReservationCategory category;
    std::string providerId;
    RequestType requestType;

  public:
    [[nodiscard]] virtual std::unique_ptr<ItineraryItem> clone() const = 0;
    virtual ~ItineraryItem() = default;

    [[nodiscard]] ReservationCategory getCategory() const
    {
        return category;
    }
    void setCategory(const ReservationCategory& c)
    {
        category = c;
    }

    [[nodiscard]] const std::string& getProviderId() const
    {
        return providerId;
    }
    void setProviderId(const std::string& id)
    {
        providerId = id;
    }

    [[nodiscard]] RequestType getRequestType() const;
    void setRequestType(const RequestType& requestType_);

    // Accept method for visitor pattern
    virtual void accept(ItineraryItemVisitor& visitor) const = 0;
};
