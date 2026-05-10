#include "flights_manager_factory.hpp"

#include "../managers/british_airways_flights_manager.hpp"
#include "../managers/air_france_flights_manager.hpp"

#include "../../model/reservation.hpp"

std::unique_ptr<ItineraryManager> FlightsManagerFactory::getManager(ReservationType type)
{
    if (type == ReservationType::britishAirways)
        return std::make_unique<BritishAirwaysFlightsManager>();

    else if (type == ReservationType::airFrance)
        return std::make_unique<AirFranceFlightsManager>();

    return nullptr;
}

std::vector<std::unique_ptr<ItineraryManager>> FlightsManagerFactory::getManagers()
{
    std::vector<std::unique_ptr<ItineraryManager>> managers{};
    managers.push_back(std::make_unique<BritishAirwaysFlightsManager>());
    managers.push_back(std::make_unique<AirFranceFlightsManager>());

    return managers;
}