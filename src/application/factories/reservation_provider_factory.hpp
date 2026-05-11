#pragma once

#include <memory>
#include <vector>

enum class ReservationType;
class ReservationProvider;

class ReservationProviderFactory
{
public:
    [[nodiscard]] virtual std::unique_ptr<ReservationProvider> getProvider(ReservationType type) const = 0;

    [[nodiscard]] virtual std::vector<std::unique_ptr<ReservationProvider>> getProviders() const = 0;

    virtual ~ReservationProviderFactory() = default;
};
