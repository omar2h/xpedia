#include "itinerariesManager.h"
#include "reservation.h"
#include "database.h"
#include "idGenerator.h"
#include <iostream>

json ItinerariesManager::convert_itinerary_to_json(const Itinerary &itinerary)
{
    json objects = json::array();
    std::vector<Reservation *> reservations = itinerary.getReservations();
    for (const Reservation *res : reservations)
    {
        std::cout << res->toJson() << "res json\n";
        objects.push_back(res->toJson());
    }
    return objects;
}

void ItinerariesManager::save_itinerary(const std::string &customerId, const Itinerary &itinerary)
{
    json objectsReservations = convert_itinerary_to_json(itinerary);
    std::cout << objectsReservations;
    json obj;
    obj["reservations"] = objectsReservations;
    obj["customer_id"] = customerId;
    obj["id"] = itinerary.getId();
    Database::get_database()->write_json_to_file(ITINERARIES_JSON, obj, true);
}
