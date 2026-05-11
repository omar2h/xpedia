#pragma once

#include <string>
#include <memory>

#include "../third_party/json.hpp"
using json = nlohmann::json;

#include "itinerary_item.hpp"
#include "visitors/reservation_visitor.hpp"

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
    RequestType reqType;

public:
    virtual std::unique_ptr<Reservation> clone() const = 0;

    virtual double total_cost() const = 0;

    virtual std::string toString() const = 0;

    virtual std::string toSummaryString() const = 0;

    virtual void accept(ReservationVisitor &) const = 0;

    virtual void setRequest(std::unique_ptr<ReservationRequest>) = 0;
    virtual void setItem(ItineraryItem *const) = 0;
    ReservationType getType() const { return type; }
    void setType(ItineraryItem const *item) { type = item->getType(); }

    virtual ~Reservation() = default;

    RequestType getReqType() const { return reqType; }
    void setReqType(ItineraryItem const *item) { reqType = item->getReqType(); }
};
