#ifndef __FLIGHTSMANAGERFACTORY_H__
#define __FLIGHTSMANAGERFACTORY_H__
#include "itineraryManagerFactory.h"
#include "../../backend/flightsManager.h"
#include <vector>

enum class ReservationType;
class FlightsManagerFactory : public ItineraryManagerFactory
{
public:
    ItineraryManager *getManager(ReservationType);
    static std::vector<ItineraryManager *> getManagers();
};
#endif // __FLIGHTSMANAGERFACTORY_H__