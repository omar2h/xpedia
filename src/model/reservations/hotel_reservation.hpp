#pragma once

#include "../reservation.hpp"
#include "../requests/hotel_request.hpp"
#include <memory>

class HotelRoom;

class HotelReservation : public Reservation
{
    std::unique_ptr<HotelRequest> request{};
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
    HotelReservation() = default;
    HotelReservation(const HotelReservation &);
    HotelReservation &operator=(const HotelReservation &);
    HotelReservation(HotelReservation &&) noexcept = default;
    HotelReservation &operator=(HotelReservation &&) noexcept = default;

    Reservation *Clone() const override;

    double total_cost() const override;

    std::string toString() const override;

    std::string toString2() const override;

    void setRequest(std::unique_ptr<ReservationRequest>) override;

    void setItem(ItineraryItem *const) override;

    json toJson() const override;

    static std::unique_ptr<Reservation> fromJson(const json &);

    std::unique_ptr<Reservation> jsonToReservation(json) override;

    void setAttributes(const std::string &, const std::string &, const std::string &, const std::string &, int, int, double, const std::string & = "", int = 0) override;

    ~HotelReservation() override;
};
