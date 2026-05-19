#pragma once

#include <string>

struct HotelSearchInput
{
    std::string city;
    std::string fromDate;
    std::string toDate;
    int adults{};
    int children{};
    int rooms{};
};
