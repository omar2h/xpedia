#pragma once

#include "reservation.hpp"
#include "hotel_room.hpp"

class HotelReservation : public Reservation
{
    HotelRoom room;
    bool hasRoom{};
    std::string city{};
    int adults{};
    int children{};
    int rooms{};
    double cost{};

    void recalculateCost();

public:
    HotelReservation() = default;
    HotelReservation(const HotelReservation &) = default;
    HotelReservation &operator=(const HotelReservation &) = default;
    HotelReservation(HotelReservation &&) noexcept = default;
    HotelReservation &operator=(HotelReservation &&) noexcept = default;
    ~HotelReservation() = default;

    [[nodiscard]] std::unique_ptr<Reservation> clone() const override;

    void accept(ReservationVisitor &) const override;

    [[nodiscard]] double totalCost() const override;

    void setItem(const ItineraryItem &) override;

    void applyRequest(const ReservationRequest &) override;

    void setHotelName(const std::string &name) { room.setHotelName(name); }
    void setFromDate(const std::string &d) { room.setDateFrom(d); }
    void setToDate(const std::string &d) { room.setDateTo(d); }
    void setCity(const std::string &c) { city = c; }
    void setRoomType(const std::string &rt) { room.setRoomType(rt); }
    void setAdults(int a) { adults = a; }
    void setChildren(int c) { children = c; }
    void setRooms(int r) { rooms = r; }
    void setCost(double c) { cost = c; }

    [[nodiscard]] const std::string &getHotelName() const { return room.getHotelName(); }
    [[nodiscard]] const std::string &getFromDate() const { return room.getDateFrom(); }
    [[nodiscard]] const std::string &getToDate() const { return room.getDateTo(); }
    [[nodiscard]] const std::string &getCity() const { return city; }
    [[nodiscard]] const std::string &getRoomType() const { return room.getRoomType(); }
    [[nodiscard]] int getRooms() const { return rooms; }
    [[nodiscard]] int getAdults() const { return adults; }
    [[nodiscard]] int getChildren() const { return children; }
};
