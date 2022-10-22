#include "flightsManagerFactory.h"
#include "airCanadaFlightsManager.h"
#include "turkishFlightsManager.h"

std::vector<FlightsManager *> FlightsManagerFactory::getManagers()
{
    std::vector<FlightsManager *> managers{};
    managers.push_back(new AirCanadaFlightsManager);
    managers.push_back(new TurkishFlightsManager);
    return managers;
}