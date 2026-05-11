#pragma once

#include "../../application/factories/reservation_provider_factory.hpp"
#include "providers/flight_provider.hpp"
#include <vector>

class FlightProviderFactory : public ReservationProviderFactory
{
public:
    [[nodiscard]] std::unique_ptr<ReservationProvider> getProvider(ReservationType) const override;

    [[nodiscard]] std::vector<std::unique_ptr<ReservationProvider>> getProviders() const override;
};
