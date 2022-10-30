#ifndef __HOTELREQUEST_H__
#define __HOTELREQUEST_H__
#include "reservationRequest.h"

class HotelRequest : public ReservationRequest
{
    std::string fromDate{};
    std::string toDate{};
    std::string city{};
    int rooms;
    int adults{};
    int children{};

public:
    HotelRequest() = default;
    HotelRequest(const std::string &, const std::string &, const std::string &, int, int);
    ReservationRequest *Clone() override;
    std::string toString() const override;

    std::string getFromDate() const { return fromDate; }
    void setFromDate(const std::string &fromDate_) { fromDate = fromDate_; }

    std::string getToDate() const { return toDate; }
    void setToDate(const std::string &toDate_) { toDate = toDate_; }

    std::string getCity() const { return city; }
    void setCity(const std::string &city_) { city = city_; }

    int getAdults() const { return adults; }
    void setAdults(int adults_) { adults = adults_; }

    int getChildren() const { return children; }
    void setChildren(int children_) { children = children_; }

    int getRooms() const { return rooms; }
    void setRooms(int rooms_) { rooms = rooms_; }

    ~HotelRequest() override = default;
};
#endif // __HOTELREQUEST_H__