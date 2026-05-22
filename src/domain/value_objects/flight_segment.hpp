#pragma once

#include <string>

#include "airline.hpp"

struct FlightSegment
{
    Airline airline;

    std::string flightNumber;

    std::string fromIata;
    std::string toIata;

    std::string departureTime;
    std::string arrivalTime;

    std::string aircraft;
    std::string cabinClass;

    int checkedBagQuantity{};
};