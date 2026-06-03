#pragma once

#include <memory>
#include <string>

#include "../request_type.hpp"
#include "../visitors/reservation_visitor.hpp"
#include "itinerary_item.hpp"
#include "reservation_category.hpp"

class Reservation
{
    ReservationCategory category{};
    std::string providerId;
    RequestType requestType{};

  public:
    virtual ~Reservation() = default;

    [[nodiscard]] virtual std::unique_ptr<Reservation> clone() const = 0;

    [[nodiscard]] virtual double totalCost() const = 0;

    virtual void accept(ReservationVisitor& visitor) const = 0;

    virtual void setItem(const ItineraryItem& item) = 0;

    [[nodiscard]] ReservationCategory getCategory() const
    {
        return category;
    }

    void setCategory(ReservationCategory c)
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

    [[nodiscard]] RequestType getRequestType() const
    {
        return requestType;
    }

    void setRequestType(RequestType type)
    {
        requestType = type;
    }
};
