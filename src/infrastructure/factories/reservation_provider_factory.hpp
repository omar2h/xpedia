#pragma once

#include "../../application/factories/reservation_provider_factory.hpp"

class RoutingReservationProviderFactory : public ReservationProviderFactory
{
public:
    [[nodiscard]] std::unique_ptr<ReservationProvider> getProvider(ReservationType type) const override;

    [[nodiscard]] std::vector<std::unique_ptr<ReservationProvider>> getProviders() const override;
};
