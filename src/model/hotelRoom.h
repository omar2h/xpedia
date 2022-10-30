#ifndef __HOTELROOM_H__
#define __HOTELROOM_H__
#include "itineraryItem.h"

class HotelRoom : public ItineraryItem
{
    std::string hotelName{};
    std::string roomType{};
    int availableRooms{};
    double pricePerNight{};
    std::string dateFrom{};
    std::string dateTo{};

public:
    std::string toString() const override;
    ItineraryItem *Clone() override;
    virtual ~HotelRoom() = default;

    std::string getHotelName() const { return hotelName; }
    void setHotelName(const std::string &hotelName_) { hotelName = hotelName_; }

    std::string getRoomType() const { return roomType; }
    void setRoomType(const std::string &roomType_) { roomType = roomType_; }

    int getAvailableRooms() const { return availableRooms; }
    void setAvailableRooms(int availableRooms_) { availableRooms = availableRooms_; }

    double getPricePerNight() const { return pricePerNight; }
    void setPricePerNight(double pricePerNight_) { pricePerNight = pricePerNight_; }

    std::string getDateFrom() const { return dateFrom; }
    void setDateFrom(const std::string &dateFrom_) { dateFrom = dateFrom_; }

    std::string getDateTo() const { return dateTo; }
    void setDateTo(const std::string &dateTo_) { dateTo = dateTo_; }

    double total_cost() const
    {
        return 100;
    }
};
#endif // __HOTELROOM_H__