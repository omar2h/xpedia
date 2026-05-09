#pragma once

#include "itinerary_manager_factory.hpp"
#include <vector>

class HotelsManagerFactory : public ItineraryManagerFactory
{
public:
    ItineraryManager *getManager(ReservationType);
    static std::vector<ItineraryManager *> getManagers();
};
