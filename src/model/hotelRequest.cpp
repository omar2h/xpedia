#include "hotelRequest.h"
#include <sstream>
HotelRequest::HotelRequest(const std::string &from, const std::string &to, const std::string &city, int adults, int children) : fromDate(from), toDate(to), city(city), adults(adults), children(children)
{
}

ReservationRequest *HotelRequest::Clone()
{
    return new HotelRequest(*this);
}

std::string HotelRequest::toString() const
{
    std::stringstream oss;
    oss << fromDate << " " << toDate << " " << city;
    return oss.str();
}
