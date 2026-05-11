#pragma once

#include "../../application/factories/reservation_provider_factory.hpp"
#include <vector>

class HotelProviderFactory : public ReservationProviderFactory
{
public:
    [[nodiscard]] std::unique_ptr<ReservationProvider> getProvider(ReservationType) const override;

    [[nodiscard]] std::vector<std::unique_ptr<ReservationProvider>> getProviders() const override;
};
