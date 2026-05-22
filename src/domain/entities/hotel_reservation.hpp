#pragma once

#include "reservation.hpp"

#include "../entities/hotel_room.hpp"
#include "../value_objects/hotel_search_request.hpp"

class HotelReservation : public Reservation
{
    HotelRoom room;

    std::string city;

    int adults{};
    int children{};
    int rooms{};

    double cost{};

    bool hasRoom{};

    void recalculateCost();

public:
    [[nodiscard]]
    const std::string &getHotelName() const { return room.getHotelName(); }
    void setHotelName(const std::string &hotelName) { room.setHotelName(hotelName); }

    [[nodiscard]]
    const std::string &getFromDate() const { return room.getDateFrom(); }
    void setFromDate(const std::string &fromDate) { room.setDateFrom(fromDate); }

    [[nodiscard]]
    const std::string &getToDate() const { return room.getDateTo(); }
    void setToDate(const std::string &toDate) { room.setDateTo(toDate); }

    [[nodiscard]]
    const std::string &getCity() const { return city; }
    void setCity(const std::string &city_) { city = city_; }

    [[nodiscard]]
    const std::string &getRoomType() const { return room.getRoomType(); }
    void setRoomType(const std::string &roomType) { room.setRoomType(roomType); }

    [[nodiscard]]
    int getRooms() const { return rooms; }
    void setRooms(int rooms_) { rooms = rooms_; }

    [[nodiscard]]
    int getAdults() const { return adults; }
    void setAdults(int adults_) { adults = adults_; }

    [[nodiscard]]
    int getChildren() const { return children; }
    void setChildren(int children_) { children = children_; }

    void setCost(double cost_) { cost = cost_; }

    [[nodiscard]]
    std::unique_ptr<Reservation>
    clone() const override;

    [[nodiscard]]
    double totalCost() const override;

    void accept(ReservationVisitor &visitor) const override;

    void setItem(const ItineraryItem &item) override;

    void applySearchRequest(const HotelSearchRequest &request);
};
