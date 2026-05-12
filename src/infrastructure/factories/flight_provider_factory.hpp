#pragma once

#include "../../application/providers/flight_provider.hpp"
#include <vector>

class FlightProviderFactory
{
public:
    [[nodiscard]] std::unique_ptr<ReservationProvider> getProvider(const std::string &providerId) const;

    [[nodiscard]] std::vector<std::unique_ptr<ReservationProvider>> getProviders() const;
};
