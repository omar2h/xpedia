#ifndef __FLIGHTREQUEST_H__
#define __FLIGHTREQUEST_H__
#include "reservationRequest.h"
#include <string>

class FlightRequest : public ReservationRequest
{
    std::string fromCity{};
    std::string toCity{};
    std::string date{};
    int adults{};
    int children{};

public:
    FlightRequest() = default;
    FlightRequest(const std::string &, const std::string &, const std::string &, int, int);

    ReservationRequest *Clone() override;

    int getAdults() const { return adults; }
    void setAdults(int adults_) { adults = adults_; }

    int getChildren() const { return children; }
    void setChildren(int children_) { children = children_; }

    std::string getFromCity() const { return fromCity; }
    void setFromCity(const std::string &fromCity_) { fromCity = fromCity_; }

    std::string getToCity() const { return toCity; }
    void setToCity(const std::string &toCity_) { toCity = toCity_; }

    std::string getDate() const { return date; }
    void setDate(const std::string &date_) { date = date_; }
};
#endif // __FLIGHTREQUEST_H__