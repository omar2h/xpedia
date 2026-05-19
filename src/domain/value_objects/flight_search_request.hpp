#pragma once

#include <string>

struct FlightSearchRequest
{
    std::string origin;
    std::string destination;
    std::string departureDate;
    int adults = 1;
};
