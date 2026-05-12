#pragma once

#include <string>
#include <memory>

#include "../request_type.hpp"
#include "reservation_category.hpp"

class ItineraryItem
{
    ReservationCategory category;
    std::string providerId;
    RequestType requestType;

public:
    [[nodiscard]] virtual std::unique_ptr<ItineraryItem> clone() const = 0;
    virtual ~ItineraryItem() = default;

    ReservationCategory getCategory() const { return category; }
    void setCategory(const ReservationCategory &c) { category = c; }

    const std::string &getProviderId() const { return providerId; }
    void setProviderId(const std::string &id) { providerId = id; }

    RequestType getRequestType() const;
    void setRequestType(const RequestType &requestType_);
};
