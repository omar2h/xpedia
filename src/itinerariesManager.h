#ifndef __ITINERARIESMANAGER_H__
#define __ITINERARIESMANAGER_H__
#include "itinerary.h"
#include "include/json.hpp"
#include <unordered_set>
using json = nlohmann::json;

class ItinerariesManager
{
    std::unordered_set<std::string> itinerariesIds{};

public:
    json convert_itinerary_to_json(const Itinerary &);
    void save_itinerary(const std::string &, const Itinerary &);
};
#endif // __ITINERARIESMANAGER_H__