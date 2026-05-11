#pragma once

#include <memory>
#include <vector>

enum class ReservationType;
class ReservationProvider;

class RoutingReservationProviderFactory
{
public:
    [[nodiscard]] std::unique_ptr<ReservationProvider> getProvider(ReservationType type) const;

    [[nodiscard]] std::vector<std::unique_ptr<ReservationProvider>> getProviders() const;
};
