#include "../../model/json_keys.hpp"
#include "../storage/file_storage.hpp"
#include "../mappers/itinerary_mapper.hpp"
#include "itinerary_repository.hpp"

ItineraryRepository::ItineraryRepository(FileStorage &storage_)
    : storage(storage_)
{
}

void ItineraryRepository::save(const std::string &customerId, const Itinerary &itinerary) const
{
    json obj = ItineraryMapper::toJson(itinerary);

    obj[JsonKeys::customerId] = customerId;
    storage.writeJsonToFile("itineraries.json", obj, true);
}

std::vector<Itinerary> ItineraryRepository::findByCustomerId(const std::string &customerId) const
{
    json arr = storage.getObjectsWithAttribute("itineraries.json", JsonKeys::customerId, customerId);

    std::vector<Itinerary> itineraries;

    for (const auto &obj : arr)
    {
        itineraries.push_back(ItineraryMapper::fromJson(obj));
    }

    return itineraries;
}