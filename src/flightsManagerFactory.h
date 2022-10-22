#ifndef __FLIGHTSMANAGERFACTORY_H__
#define __FLIGHTSMANAGERFACTORY_H__
#include "flightsManager.h"
#include <vector>

class FlightsManagerFactory
{
public:
    static std::vector<FlightsManager *> getManagers();
};
#endif // __FLIGHTSMANAGERFACTORY_H__