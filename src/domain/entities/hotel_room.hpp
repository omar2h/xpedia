#pragma once

#include "../visitors/itinerary_item_visitor.hpp"
#include "itinerary_item.hpp"

class HotelRoom : public ItineraryItem
{
    std::string hotelName{};
    std::string roomType{};
    int availableRooms{};
    double pricePerNight{};
    std::string dateFrom{};
    std::string dateTo{};

  public:
    [[nodiscard]] std::unique_ptr<ItineraryItem> clone() const override
    {
        return std::make_unique<HotelRoom>(*this);
    }
    void accept(ItineraryItemVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
    virtual ~HotelRoom() = default;

    [[nodiscard]] const std::string& getHotelName() const
    {
        return hotelName;
    }
    void setHotelName(const std::string& hotelName_)
    {
        hotelName = hotelName_;
    }

    [[nodiscard]] const std::string& getRoomType() const
    {
        return roomType;
    }
    void setRoomType(const std::string& roomType_)
    {
        roomType = roomType_;
    }

    [[nodiscard]] int getAvailableRooms() const
    {
        return availableRooms;
    }
    void setAvailableRooms(int availableRooms_)
    {
        availableRooms = availableRooms_;
    }

    [[nodiscard]] double getPricePerNight() const
    {
        return pricePerNight;
    }
    void setPricePerNight(double pricePerNight_)
    {
        pricePerNight = pricePerNight_;
    }

    [[nodiscard]] const std::string& getDateFrom() const
    {
        return dateFrom;
    }
    void setDateFrom(const std::string& dateFrom_)
    {
        dateFrom = dateFrom_;
    }

    [[nodiscard]] const std::string& getDateTo() const
    {
        return dateTo;
    }
    void setDateTo(const std::string& dateTo_)
    {
        dateTo = dateTo_;
    }

    [[nodiscard]] double totalCost() const
    {
        return pricePerNight;
    }
};
