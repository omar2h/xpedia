#include "itinerary_mapper.hpp"

#include "../../infrastructure/json_keys.hpp"
#include "../../infrastructure/serialization/reservation_serializer.hpp"

json ItineraryMapper::toJson(const Itinerary &itinerary)
{
    json obj;

    json reservations = json::array();

    ReservationSerializer serializer;

    for (const auto &res : itinerary.getReservations())
    {
        reservations.push_back(serializer.toJson(*res));
    }

    obj[JsonKeys::reservations] = reservations;
    obj[JsonKeys::id] = itinerary.getId();
    obj[JsonKeys::cost] = itinerary.totalCost();

    return obj;
}

Itinerary ItineraryMapper::fromJson(const json &obj)
{
    Itinerary itinerary;

    itinerary.setId(obj.value(JsonKeys::id, "not found"));

    itinerary.setCost(obj.value(JsonKeys::cost, -1.0));

    json arr = obj[JsonKeys::reservations];

    for (const auto &resObj : arr)
    {
        itinerary.addItem(ReservationSerializer::fromJson(resObj));
    }

    return itinerary;
}