#ifndef __FLIGHTSMANAGERFACTORY_H__
#define __FLIGHTSMANAGERFACTORY_H__
#include "flightsManager.h"
#include <vector>

class FlightsManagerFactory
{
public:
    static std::vector<ItineraryManager *> getManagers();
};
#endif // __FLIGHTSMANAGERFACTORY_H__