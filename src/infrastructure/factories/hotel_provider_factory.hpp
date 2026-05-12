#pragma once

#include <memory>
#include <vector>
#include <string>

class ReservationProvider;

class HotelProviderFactory
{
public:
    [[nodiscard]] std::unique_ptr<ReservationProvider> getProvider(const std::string &providerId) const;

    [[nodiscard]] std::vector<std::unique_ptr<ReservationProvider>> getProviders() const;
};
