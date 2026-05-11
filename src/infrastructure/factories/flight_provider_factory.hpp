#pragma once

#include "reservation_provider_factory.hpp"
#include "providers/flight_provider.hpp"
#include <vector>

enum class ReservationType;
class FlightProviderFactory : public ReservationProviderFactory
{
public:
    std::unique_ptr<ReservationProvider> getProvider(ReservationType) override;
    std::vector<std::unique_ptr<ReservationProvider>> getProviders();
};
