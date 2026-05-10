// #include "itineraries_manager.hpp"
// #include "../model/reservation.hpp"
// #include "../db/database.hpp"
// #include "../db/id_generator.hpp"
// #include "../model/serializers/reservation_serializer.hpp"
// #include <iostream>

// json ItinerariesManager::convert_itinerary_to_json(const Itinerary &itinerary)
// {
//     ReservationSerializer serializer;
//     json objects = json::array();
//     const auto &reservations = itinerary.getReservations();
//     for (const auto &res : reservations)
//     {
//         objects.push_back(serializer.to_json(*res));
//     }
//     return objects;
// }

// void ItinerariesManager::save_itinerary(const std::string &customerId, const Itinerary &itinerary)
// {
//     json objectsReservations = convert_itinerary_to_json(itinerary);
//     std::cout << objectsReservations;
//     json obj;
//     obj["reservations"] = objectsReservations;
//     obj["customer_id"] = customerId;
//     obj["id"] = itinerary.getId();
//     obj["cost"] = itinerary.total_cost();
//     Database::get_database()->write_json_to_file(ITINERARIES_JSON, obj, true);
// }

// std::unique_ptr<Reservation> ItinerariesManager::convert_json_to_reservation(json obj)
// {
//     return ReservationSerializer::from_json(obj);
// }

// Itinerary ItinerariesManager::convert_json_to_itinerary(json obj)
// {
//     Itinerary itinerary;
//     itinerary.setId(obj.value("id", "not found"));
//     itinerary.setCost(obj.value("cost", -1));
//     json arr = json::array();
//     arr = obj["reservations"];

//     for (const auto &resObj : arr)
//     {
//         itinerary.add_item(convert_json_to_reservation(resObj));
//     }
//     return itinerary;
// }

// std::vector<Itinerary> ItinerariesManager::getItineraries_with_customerId(const std::string &customerId)
// {
//     json arr;

//     arr = Database::get_database()->get_arr_objects_with_att(ITINERARIES_JSON, "customer_id", customerId);

//     std::vector<Itinerary> itineraries;
//     for (json obj : arr)
//     {
//         Itinerary itinerary;
//         itinerary = convert_json_to_itinerary(obj);
//         itineraries.push_back(itinerary);
//     }
//     return itineraries;
// }
