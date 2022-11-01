#ifndef __HOTELRESERVATION_H__
#define __HOTELRESERVATION_H__
#include "reservation.h"

class HotelRequest;
class HotelRoom;

class HotelReservation : public Reservation
{
    HotelRequest *request{};
    HotelRoom *item{};
    std::string hotelName{};
    std::string fromDate{};
    std::string toDate{};
    std::string city{};
    std::string roomType{};
    int adults{};
    int children{};
    int rooms{};
    double cost{};

public:
    Reservation *Clone() const override { return new HotelReservation(*this); }

    double total_cost() const override;

    std::string toString() const override;

    std::string toString2() const override;

    void setRequest(ReservationRequest *const) override;

    void setItem(ItineraryItem *const) override;

    json toJson() const override;

    Reservation *jsonToReservation(json) override;

    void setAttributes(const std::string &, const std::string &, const std::string &, const std::string &, int, int, double, const std::string & = "", int = 0) override;

    ~HotelReservation() override;
};
#endif // __HOTELRESERVATION_H__