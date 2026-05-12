#include "flight_provider_factory.hpp"

#include "providers/british_airways_flight_provider.hpp"
#include "providers/air_france_flight_provider.hpp"

#include <string>

std::unique_ptr<ReservationProvider> FlightProviderFactory::getProvider(const std::string &providerId) const
{
    if (providerId == "british_airways")
        return std::make_unique<BritishAirwaysFlightProvider>();

    else if (providerId == "air_france")
        return std::make_unique<AirFranceFlightProvider>();

    return nullptr;
}

std::vector<std::unique_ptr<ReservationProvider>> FlightProviderFactory::getProviders() const
{
    std::vector<std::unique_ptr<ReservationProvider>> providers{};
    providers.push_back(std::make_unique<BritishAirwaysFlightProvider>());
    providers.push_back(std::make_unique<AirFranceFlightProvider>());

    return providers;
}
