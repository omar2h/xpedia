#pragma once

#include "../../model/itinerary.hpp"

#include "../../model/serializers/reservation_serializer.hpp"

#include "../../include/json.hpp"

using json = nlohmann::json;

class ItineraryRepository
{
public:
    void save(const std::string &customerId, const Itinerary &) const;

    std::vector<Itinerary> findByCustomerId(const std::string &) const;

private:
    json to_json(const Itinerary &) const;

    Itinerary from_json(const json &) const;
};