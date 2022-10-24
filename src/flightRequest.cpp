#include "flightRequest.h"
#include <sstream>

FlightRequest::FlightRequest(const std::string &from, const std::string &to, const std::string &date, int adults,
                             int children) : fromCity{from}, toCity{to}, date{date}, adults{adults}, children{children}
{
}

ReservationRequest *FlightRequest::Clone()
{
    return new FlightRequest(*this);
}

std::string FlightRequest::toString() const
{
    std::stringstream oss;
    oss << getFromCity() << " " << getToCity() << " " << getDate();
    return oss.str();
}
