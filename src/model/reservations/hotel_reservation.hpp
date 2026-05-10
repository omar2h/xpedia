#pragma once

#include "../reservation.hpp"
#include <memory>

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

    static std::unique_ptr<Reservation> fromJson(const json &);

    std::unique_ptr<Reservation> jsonToReservation(json) override;

    void setAttributes(const std::string &, const std::string &, const std::string &, const std::string &, int, int, double, const std::string & = "", int = 0) override;

    ~HotelReservation() override;
};
