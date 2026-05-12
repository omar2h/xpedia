#pragma once

#include <memory>
#include <string>
#include <vector>

#include "../../domain/entities/reservation_category.hpp"

class ReservationProvider;

class RoutingReservationProviderFactory
{
public:
    [[nodiscard]] std::unique_ptr<ReservationProvider> getProvider(ReservationCategory category, const std::string &providerId) const;

    [[nodiscard]] std::vector<std::unique_ptr<ReservationProvider>> getProviders() const;
};
