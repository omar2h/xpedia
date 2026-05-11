#pragma once

#include "reservation_provider_factory.hpp"
#include <vector>

class HotelProviderFactory : public ReservationProviderFactory
{
public:
    std::unique_ptr<ReservationProvider> getProvider(ReservationType) const;
    std::vector<std::unique_ptr<ReservationProvider>> getProviders() const;
};
