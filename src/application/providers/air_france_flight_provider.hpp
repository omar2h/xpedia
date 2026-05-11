#pragma once

#include "flight_provider.hpp"

class AirFranceFlightProvider : public FlightProvider
{
public:
    std::string getName() const override
    {
        return "AirFrance";
    }

    std::vector<std::unique_ptr<ItineraryItem>> searchReservations() const override;

    bool reserve(Reservation *reservation) const override;

    std::unique_ptr<ReservationProvider> clone() const override { return std::make_unique<AirFranceFlightProvider>(*this); }

    ~AirFranceFlightProvider() override = default;
};
