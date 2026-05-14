#pragma once

#include <string>
#include <memory>

#include "itinerary_item.hpp"
#include "../visitors/reservation_visitor.hpp"
#include "../request_type.hpp"
#include "reservation_category.hpp"

class ReservationRequest;

class Reservation
{
    ReservationCategory category;
    std::string providerId;
    RequestType requestType;

public:
    [[nodiscard]] virtual std::unique_ptr<Reservation> clone() const = 0;

    [[nodiscard]] virtual double totalCost() const = 0;

    virtual void accept(ReservationVisitor &) const = 0;

    virtual void setItem(const ItineraryItem &) = 0;

    virtual void applyRequest(const ReservationRequest &) = 0;

    [[nodiscard]] ReservationCategory getCategory() const { return category; }
    void setCategory(ReservationCategory c) { category = c; }
    void setCategory(const ItineraryItem *item) { category = item->getCategory(); }

    [[nodiscard]] const std::string &getProviderId() const { return providerId; }
    void setProviderId(const std::string &id) { providerId = id; }
    void copyProviderFrom(const ItineraryItem *item) { providerId = item->getProviderId(); }

    virtual ~Reservation() = default;

    [[nodiscard]] RequestType getRequestType() const { return requestType; }
    void setRequestType(ItineraryItem const *item) { requestType = item->getRequestType(); }
    void setRequestType(RequestType rt) { requestType = rt; }
};
