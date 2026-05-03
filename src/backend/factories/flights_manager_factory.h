#ifndef __FLIGHTSMANAGERFACTORY_H__
#define __FLIGHTSMANAGERFACTORY_H__
#include "itinerary_manager_factory.h"
#include "../managers/flights_manager.h"
#include <vector>

enum class ReservationType;
class FlightsManagerFactory : public ItineraryManagerFactory
{
public:
    ItineraryManager *getManager(ReservationType);
    static std::vector<ItineraryManager *> getManagers();
};
#endif // __FLIGHTSMANAGERFACTORY_H__
