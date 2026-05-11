#pragma once

#include <memory>
#include <vector>

enum class ReservationType;
class ReservationProvider;

class HotelProviderFactory
{
public:
    [[nodiscard]] std::unique_ptr<ReservationProvider> getProvider(ReservationType) const;

    [[nodiscard]] std::vector<std::unique_ptr<ReservationProvider>> getProviders() const;
};
