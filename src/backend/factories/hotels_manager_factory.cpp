#include "hotels_manager_factory.hpp"
#include "../managers/marriott_hotels_manager.hpp"
#include "../managers/hilton_hotels_manager.hpp"
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
