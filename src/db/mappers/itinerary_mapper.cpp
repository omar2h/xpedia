#include "itinerary_mapper.hpp"

#include "../../model/serializers/reservation_serializer.hpp"

json ItineraryMapper::to_json(const Itinerary &itinerary)
{
    json obj;

    json reservations = json::array();

    ReservationSerializer serializer;

    for (const auto &res : itinerary.getReservations())
    {
        reservations.push_back(serializer.to_json(*res));
    }

    obj["reservations"] = reservations;
    obj["id"] = itinerary.getId();
    obj["cost"] = itinerary.total_cost();

    return obj;
}

Itinerary ItineraryMapper::from_json(const json &obj)
{
    Itinerary itinerary;

    itinerary.setId(obj.value("id", "not found"));

    itinerary.setCost(obj.value("cost", -1.0));

    json arr = obj["reservations"];

    for (const auto &resObj : arr)
    {
        itinerary.add_item(ReservationSerializer::from_json(resObj));
    }

    return itinerary;
}