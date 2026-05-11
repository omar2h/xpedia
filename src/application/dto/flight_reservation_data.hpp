#pragma once

#include <string>

struct FlightReservationData
{
    std::string airline;
    std::string from;
    std::string to;
    std::string date;

    int adults{};
    int children{};

    double cost{};
};