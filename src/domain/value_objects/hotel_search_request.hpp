#pragma once

#include <string>
#include <vector>

struct HotelSearchRequest
{
    std::string city;

    double latitude = 0.0;
    double longitude = 0.0;

    std::string checkInDate;
    std::string checkOutDate;

    int adults = 1;
    int rooms = 1;

    std::vector<int> childAges;
};