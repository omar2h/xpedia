#include "flightsManagerFactory.h"
#include "../../backend/britishAirwaysFlightsManager.h"
#include "../../backend/airFranceFlightsManager.h"
#include "../../model/reservation.h"

ItineraryManager *FlightsManagerFactory::getManager(ReservationType type)
{
    if (type == ReservationType::britishAirways)
        return new BritishAirwaysFlightsManager;
    else if (type == ReservationType::airFrance)
        return new AirFranceFlightsManager;
}

std::vector<ItineraryManager *> FlightsManagerFactory::getManagers()
{
    std::vector<ItineraryManager *> managers{};
    managers.push_back(new BritishAirwaysFlightsManager);
    managers.push_back(new AirFranceFlightsManager);
    return managers;
}