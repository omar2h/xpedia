#include "flights_manager_factory.hpp"
#include "../managers/british_airways_flights_manager.hpp"
#include "../managers/air_france_flights_manager.hpp"
#include "../../model/reservation.hpp"

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
