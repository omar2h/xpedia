#pragma once

#include <string>

struct HotelSearchRequest
{
    std::string city;

    std::string checkInDate;
    std::string checkOutDate;

    int adults{};
    int children{};
    int rooms{};
};