#pragma once

#include "reservation.hpp"
#include "hotel_room.hpp"
#include <memory>

class HotelReservation : public Reservation
{
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
    HotelReservation &operator=(const HotelReservation &);
    HotelReservation(HotelReservation &&) noexcept = default;
    HotelReservation &operator=(HotelReservation &&) noexcept = default;
    ~HotelReservation() = default;

    [[nodiscard]] std::unique_ptr<Reservation> clone() const override;

    void accept(ReservationVisitor &) const override;

    [[nodiscard]] double totalCost() const override;

    [[nodiscard]] std::string toString() const override;

    [[nodiscard]] std::string toSummaryString() const override;

    void setItem(const ItineraryItem &) override;

    // Setters for domain state
    void setHotelName(const std::string &name) { hotelName = name; }
    void setFromDate(const std::string &d) { fromDate = d; }
    void setToDate(const std::string &d) { toDate = d; }
    void setCity(const std::string &c) { city = c; }
    void setRoomType(const std::string &rt) { roomType = rt; }
    void setAdults(int a) { adults = a; }
    void setChildren(int c) { children = c; }
    void setRooms(int r) { rooms = r; }
    void setCost(double c) { cost = c; }

    std::string getHotelName() const { return hotelName; }
    std::string getFromDate() const { return fromDate; }
    std::string getToDate() const { return toDate; }
    std::string getCity() const { return city; }
    std::string getRoomType() const { return roomType; }
    int getRooms() const { return rooms; }
    int getAdults() const { return adults; }
    int getChildren() const { return children; }
};
