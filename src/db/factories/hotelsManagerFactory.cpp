#include "hotelsManagerFactory.h"
#include "../../backend/marriottHotelsManager.h"
#include "../../backend/hiltonHotelsManager.h"
ItineraryManager *HotelsManagerFactory::getManager(ReservationType type)
{
    if (type == ReservationType::marriott)
        return new MarriottHotelsManager;
    else if (type == ReservationType::hilton)
        return new HiltonHotelsManager;
}

std::vector<ItineraryManager *> HotelsManagerFactory::getManagers()
{
    std::vector<ItineraryManager *> managers;
    managers.push_back(new MarriottHotelsManager);
    managers.push_back(new HiltonHotelsManager);
    return managers;
}
