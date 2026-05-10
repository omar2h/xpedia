#include "../storage/file_storage.hpp"

#include "../database.hpp"

json ItineraryRepository::to_json(const Itinerary &itinerary) const
{
    json objects = json::array();

    const auto &reservations = itinerary.getReservations();

    ReservationSerializer serializer;

    for (const auto &res : reservations)
    {
        objects.push_back(serializer.to_json(*res));
    }

    return objects;
}

void ItineraryRepository::save(const std::string &customerId, const Itinerary &itinerary) const
{
    FileStorage storage;
    json obj;

    obj["reservations"] = to_json(itinerary);
    obj["customer_id"] = customerId;
    obj["id"] = itinerary.getId();
    obj["cost"] = itinerary.total_cost();

    storage.write_json_to_file(
        ITINERARIES_JSON,
        obj,
        true);
}

Itinerary ItineraryRepository::from_json(const json &obj) const
{
    Itinerary itinerary;

    itinerary.setId(obj.value("id", "not found"));
    itinerary.setCost(obj.value("cost", -1.0));

    json arr = obj["reservations"];

    for (const auto &resObj : arr)
    {
        itinerary.add_item(
            ReservationSerializer::from_json(resObj));
    }

    return itinerary;
}

std::vector<Itinerary> ItineraryRepository::findByCustomerId(const std::string &customerId) const
{
    FileStorage storage;
    json arr = storage.get_arr_objects_with_att(
        ITINERARIES_JSON,
        "customer_id",
        customerId);

    std::vector<Itinerary> itineraries;

    for (const auto &obj : arr)
    {
        itineraries.push_back(from_json(obj));
    }

    return itineraries;
}