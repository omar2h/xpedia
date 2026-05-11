#include "flight_provider_factory.hpp"

#include "providers/british_airways_flight_provider.hpp"
#include "providers/air_france_flight_provider.hpp"

#include "../model/reservation.hpp"

std::unique_ptr<ReservationProvider> FlightProviderFactory::getProvider(ReservationType type)
{
    if (type == ReservationType::britishAirways)
        return std::make_unique<BritishAirwaysFlightProvider>();

    else if (type == ReservationType::airFrance)
        return std::make_unique<AirFranceFlightProvider>();

    return nullptr;
}

std::vector<std::unique_ptr<ReservationProvider>> FlightProviderFactory::getProviders()
{
    std::vector<std::unique_ptr<ReservationProvider>> providers{};
    providers.push_back(std::make_unique<BritishAirwaysFlightProvider>());
    providers.push_back(std::make_unique<AirFranceFlightProvider>());

    return providers;
}

