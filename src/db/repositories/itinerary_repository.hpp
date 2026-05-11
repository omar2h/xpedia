#pragma once

#include "../../model/itinerary.hpp"
#include "../storage/file_storage.hpp"
#include "../../model/serializers/reservation_serializer.hpp"

#include "../../include/json.hpp"

using json = nlohmann::json;

class ItineraryRepository
{
    FileStorage &storage;

public:
    explicit ItineraryRepository(FileStorage &storage_);

    void save(const std::string &customerId, const Itinerary &itinerary) const;

    std::vector<Itinerary> findByCustomerId(const std::string &customerId) const;

private:
    json to_json(const Itinerary &itinerary) const;

    Itinerary from_json(const json &obj) const;
};