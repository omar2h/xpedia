#pragma once

#include "../reservation.hpp"
#include "../requests/hotel_request.hpp"
#include "../hotel_room.hpp"
#include <memory>

class HotelReservationData;

class HotelReservation : public Reservation
{
    std::unique_ptr<HotelRequest> request{};
    std::unique_ptr<HotelRoom> item{};
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
    explicit HotelReservation(const HotelReservationData &data);
    HotelReservation &operator=(const HotelReservation &);
    HotelReservation(HotelReservation &&) noexcept = default;
    HotelReservation &operator=(HotelReservation &&) noexcept = default;
    ~HotelReservation() = default;

    std::unique_ptr<Reservation> clone() const override;

    void accept(ReservationVisitor &) const override;

    double total_cost() const override;

    std::string toString() const override;

    std::string toSummaryString() const override;

    void setRequest(std::unique_ptr<ReservationRequest>) override;

    void setItem(ItineraryItem *const) override;

    std::string getHotelName() const
    {
        return hotelName;
    }

    std::string getFromDate() const
    {
        return fromDate;
    }

    std::string getToDate() const
    {
        return toDate;
    }

    std::string getCity() const
    {
        return city;
    }

    std::string getRoomType() const
    {
        return roomType;
    }

    int getRooms() const
    {
        return rooms;
    }

    int getAdults() const
    {
        return adults;
    }

    int getChildren() const
    {
        return children;
    }
};
