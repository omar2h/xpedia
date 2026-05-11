#pragma once

#include "../../model/itinerary.hpp"
#include "../storage/file_storage.hpp"

#include "../../third_party/json.hpp"

using json = nlohmann::json;

class ItineraryRepository
{
    FileStorage &storage;

public:
    explicit ItineraryRepository(FileStorage &storage_);

    void save(const std::string &customerId, const Itinerary &itinerary) const;

    std::vector<Itinerary> findByCustomerId(const std::string &customerId) const;
};