#pragma once

#include <string>
#include <memory>

#include "../../third_party/json.hpp"
using json = nlohmann::json;

#include "itinerary_item.hpp"
#include "../visitors/reservation_visitor.hpp"

enum class RequestType;
enum class ReservationType
{
    britishAirways,
    airFrance,
    marriott,
    hilton
};
class ReservationRequest;
class Reservation
{
    ReservationType type;
    RequestType requestType;

public:
    [[nodiscard]] virtual std::unique_ptr<Reservation> clone() const = 0;

    [[nodiscard]] virtual double totalCost() const = 0;

    [[nodiscard]] virtual std::string toString() const = 0;

    [[nodiscard]] virtual std::string toSummaryString() const = 0;

    virtual void accept(ReservationVisitor &) const = 0;

    virtual void setRequest(std::unique_ptr<ReservationRequest>) = 0;
    virtual void setItem(const ItineraryItem &) = 0;
    ReservationType getType() const { return type; }
    void setType(ItineraryItem const *item) { type = item->getType(); }

    virtual ~Reservation() = default;

    RequestType getRequestType() const { return requestType; }
    void setRequestType(ItineraryItem const *item) { requestType = item->getRequestType(); }
};
