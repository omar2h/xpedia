#pragma once

#include <string>

struct FlightSearchInput
{
    std::string origin{};
    std::string destination{};
    std::string departureDate{};

    int adults{1};
};
