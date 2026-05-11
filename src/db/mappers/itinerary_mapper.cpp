#include "itinerary_mapper.hpp"

#include "../../model/serializers/reservation_serializer.hpp"

json ItineraryMapper::toJson(const Itinerary &itinerary)
{
    json obj;

    json reservations = json::array();

    ReservationSerializer serializer;

    for (const auto &res : itinerary.getReservations())
    {
        reservations.push_back(serializer.toJson(*res));
    }

    obj["reservations"] = reservations;
    obj["id"] = itinerary.getId();
    obj["cost"] = itinerary.totalCost();

    return obj;
}

Itinerary ItineraryMapper::fromJson(const json &obj)
{
    Itinerary itinerary;

    itinerary.setId(obj.value("id", "not found"));

    itinerary.setCost(obj.value("cost", -1.0));

    json arr = obj["reservations"];

    for (const auto &resObj : arr)
    {
        itinerary.addItem(ReservationSerializer::fromJson(resObj));
    }

    return itinerary;
}