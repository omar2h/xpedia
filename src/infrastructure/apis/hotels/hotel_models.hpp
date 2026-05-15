#pragma once

#include <string>
#include <vector>
#include <optional>

// Hotel search parameters
struct HotelSearchParams
{
    std::string city;
    std::string fromDate;
    std::string toDate;
    int adults = 1;
    int children = 0;
    int rooms = 1;
};

// Hotel room search result
struct HotelRoomResult
{
    std::string roomType;
    int available;
    double pricePerNight;
    std::string dateFrom;
    std::string dateTo;
    std::string hotelName;
    std::string hotelId;
};

// Hotel reservation parameters
struct HotelReservationParams
{
    std::string roomId;
    std::string guestName;
    std::string guestEmail;
    std::string guestPhone;
};