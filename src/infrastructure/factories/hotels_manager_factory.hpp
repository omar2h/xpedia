#pragma once

#include "itinerary_manager_factory.hpp"
#include <vector>

class HotelsManagerFactory : public ItineraryManagerFactory
{
public:
    std::unique_ptr<ItineraryManager> getManager(ReservationType);
    static std::vector<std::unique_ptr<ItineraryManager>> getManagers();
};
