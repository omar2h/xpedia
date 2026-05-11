#pragma once

#include <memory>

enum class ReservationType;
class ReservationProvider;
class ReservationProviderFactory
{
public:
    virtual std::unique_ptr<ReservationProvider> getProvider(ReservationType type);

    virtual ~ReservationProviderFactory() = default;
};
