#pragma once

#include <string>
#include <vector>

#include "flight_segment.hpp"

struct FlightOffer
{
    std::string providerId;

    std::string offerId;

    std::string totalAmount;
    std::string currency;

    std::string duration;

    std::string expiresAt;

    std::vector<FlightSegment> segments;
};