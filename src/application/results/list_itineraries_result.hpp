#pragma once

#include "../../domain/entities/itinerary.hpp"
#include <string>
#include <vector>

struct ListItinerariesResult
{
    bool success;
    std::string message;
    std::vector<Itinerary> itineraries;
};
