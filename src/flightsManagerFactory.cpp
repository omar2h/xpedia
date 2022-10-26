#include "flightsManagerFactory.h"
#include "airCanadaFlightsManager.h"
#include "turkishFlightsManager.h"
#include "reservation.h"

ItineraryManager *FlightsManagerFactory::getManager(ReservationType type)
{
    if (type == ReservationType::aircanada)
        return new AirCanadaFlightsManager;
    else if (type == ReservationType::turkish)
        return new TurkishFlightsManager;
}

std::vector<ItineraryManager *> FlightsManagerFactory::getManagers()
{
    std::vector<ItineraryManager *> managers{};
    managers.push_back(new AirCanadaFlightsManager);
    managers.push_back(new TurkishFlightsManager);
    return managers;
}