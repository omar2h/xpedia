#pragma once

#include "../../domain/entities/itinerary.hpp"

#include "../../third_party/json.hpp"

using json = nlohmann::json;

class ItineraryMapper
{
public:
    static json toJson(const Itinerary &itinerary);

    static Itinerary fromJson(const json &obj);
};