#ifndef __HOTELSMANAGERFACTORY_H__
#define __HOTELSMANAGERFACTORY_H__
#include "itinerary_manager_factory.h"
#include <vector>

class HotelsManagerFactory : public ItineraryManagerFactory
{
public:
    ItineraryManager *getManager(ReservationType);
    static std::vector<ItineraryManager *> getManagers();
};
#endif // __HOTELSMANAGERFACTORY_H__