#pragma once

#include "itinerary_manager_factory.hpp"
#include "../managers/flights_manager.hpp"
#include <vector>

enum class ReservationType;
class FlightsManagerFactory : public ItineraryManagerFactory
{
public:
    ItineraryManager *getManager(ReservationType);
    static std::vector<ItineraryManager *> getManagers();
};
