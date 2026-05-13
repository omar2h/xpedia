#pragma once

#include "../../../domain/entities/itinerary.hpp"

#include "../../../third_party/json.hpp"

using json = nlohmann::json;

class ItineraryMapper
{
public:
    [[nodiscard]] static json toJson(const Itinerary &itinerary);

    [[nodiscard]] static Itinerary fromJson(const json &obj);
};