#pragma once

#include <string>

struct HotelReservationData
{
    std::string hotelName;

    std::string fromDate;
    std::string toDate;

    std::string city;
    std::string roomType;

    int adults{};
    int children{};
    int rooms{};

    double cost{};
};