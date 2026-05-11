#include "../storage/file_storage.hpp"
#include "../mappers/itinerary_mapper.hpp"
#include "itinerary_repository.hpp"

ItineraryRepository::ItineraryRepository(FileStorage &storage_)
    : storage(storage_)
{
}

void ItineraryRepository::save(const std::string &customerId, const Itinerary &itinerary) const
{
    json obj = ItineraryMapper::to_json(itinerary);

    obj["customer_id"] = customerId;
    storage.write_json_to_file("itineraries.json", obj, true);
}

std::vector<Itinerary> ItineraryRepository::findByCustomerId(const std::string &customerId) const
{
    json arr = storage.getObjectsWithAttribute("itineraries.json", "customer_id", customerId);

    std::vector<Itinerary> itineraries;

    for (const auto &obj : arr)
    {
        itineraries.push_back(ItineraryMapper::from_json(obj));
    }

    return itineraries;
}