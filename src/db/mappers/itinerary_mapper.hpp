#pragma once

#include "../../model/itinerary.hpp"

#include "../../include/json.hpp"

using json = nlohmann::json;

class ItineraryMapper
{
public:
    static json to_json(const Itinerary &itinerary);

    static Itinerary from_json(const json &obj);
};