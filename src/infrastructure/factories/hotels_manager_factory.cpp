#include "hotels_manager_factory.hpp"
#include "managers/marriott_hotels_manager.hpp"
#include "managers/hilton_hotels_manager.hpp"
std::unique_ptr<ItineraryManager> HotelsManagerFactory::getManager(ReservationType type)
{
    if (type == ReservationType::marriott)
        return std::make_unique<MarriottHotelsManager>();
    else if (type == ReservationType::hilton)
        return std::make_unique<HiltonHotelsManager>();

    return nullptr;
}

std::vector<std::unique_ptr<ItineraryManager>> HotelsManagerFactory::getManagers()
{
    std::vector<std::unique_ptr<ItineraryManager>> managers;
    managers.push_back(std::make_unique<MarriottHotelsManager>());
    managers.push_back(std::make_unique<HiltonHotelsManager>());
    return managers;
}
