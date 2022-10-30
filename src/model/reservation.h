#ifndef __RESERVATION_H__
#define __RESERVATION_H__

#include <string>

#include "../include/json.hpp"
using json = nlohmann::json;

enum class RequestType;
enum class ReservationType
{
    britishAirways,
    airFrance,
    marriott,
    hilton
};
class ItineraryItem;
class ReservationRequest;
class Reservation
{
    ReservationType type;
    RequestType reqType;

public:
    virtual Reservation *Clone() const = 0;

    virtual double total_cost() const = 0;

    virtual std::string toString() const = 0;

    virtual std::string toString2() const = 0;

    virtual json toJson() const = 0;

    virtual Reservation *jsonToReservation(json) = 0;

    virtual void setAttributes(const std::string &, const std::string &, const std::string &, const std::string &, int, int, double, const std::string & = "", int = 0) = 0;

    virtual void setRequest(ReservationRequest *const) = 0;
    virtual void setItem(ItineraryItem *const) = 0;
    ReservationType getType() const { return type; }
    void setType(ItineraryItem const *);

    virtual ~Reservation() = default;

    RequestType getReqType() const { return reqType; }
    void setReqType(ItineraryItem const *);
};
#endif // __RESERVATION_H__