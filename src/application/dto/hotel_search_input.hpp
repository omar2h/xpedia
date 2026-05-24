#pragma once

#include <string>

struct HotelSearchInput
{
    std::string city;
    double latitude{};
    double longitude{};
    std::string fromDate;
    std::string toDate;
    int adults{};
    int children{};
    int rooms{};
};
