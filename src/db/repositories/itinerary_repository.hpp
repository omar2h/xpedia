#pragma once

#include "../../domain/entities/itinerary.hpp"
#include "../storage/file_storage.hpp"

#include "../../third_party/json.hpp"

using json = nlohmann::json;

class ItineraryRepository
{
    FileStorage &storage;

public:
    explicit ItineraryRepository(FileStorage &storage_);

    void save(const std::string &customerId, const Itinerary &itinerary) const;

    [[nodiscard]] std::vector<Itinerary> findByCustomerId(const std::string &customerId) const;
};