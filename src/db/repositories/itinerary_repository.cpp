#include "../storage/file_storage.hpp"
#include "../mappers/itinerary_mapper.hpp"

#include "../database.hpp"

ItineraryRepository::ItineraryRepository(FileStorage &storage_)
    : storage(storage_)
{
}

void ItineraryRepository::save(const std::string &customerId, const Itinerary &itinerary) const
{
    json obj = ItineraryMapper::to_json(itinerary);

    obj["customer_id"] = customerId;
    storage.write_json_to_file(ITINERARIES_JSON, obj, true);
}

std::vector<Itinerary> ItineraryRepository::findByCustomerId(const std::string &customerId) const
{
    json arr = storage.get_arr_objects_with_att(ITINERARIES_JSON, "customer_id", customerId);

    std::vector<Itinerary> itineraries;

    for (const auto &obj : arr)
    {
        itineraries.push_back(ItineraryMapper::from_json(obj));
    }

    return itineraries;
}