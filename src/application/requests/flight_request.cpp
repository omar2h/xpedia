#include "flight_request.hpp"
#include <memory>
#include <sstream>

FlightRequest::FlightRequest(const std::string &from, const std::string &to, const std::string &date, int adults,
                             int children) : fromCity{from}, toCity{to}, date{date}, adults{adults}, children{children}
{
}

std::unique_ptr<ReservationRequest> FlightRequest::clone()
{
    return std::make_unique<FlightRequest>(*this);
}

std::string FlightRequest::toString() const
{
    std::stringstream oss;
    oss << getFromCity() << " " << getToCity() << " " << getDate();
    return oss.str();
}
