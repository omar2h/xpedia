#pragma once

#include <string>
#include <vector>
#include "../../model/itinerary.hpp"

struct ListItinerariesResult
{
    bool success;
    std::string message;
    std::vector<Itinerary> itineraries;
};
