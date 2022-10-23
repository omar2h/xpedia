#include "flightsManagerFactory.h"
#include "airCanadaFlightsManager.h"
#include "turkishFlightsManager.h"

std::vector<ItineraryManager *> FlightsManagerFactory::getManagers()
{
    std::vector<ItineraryManager *> managers{};
    managers.push_back(new AirCanadaFlightsManager);
    managers.push_back(new TurkishFlightsManager);
    return managers;
}