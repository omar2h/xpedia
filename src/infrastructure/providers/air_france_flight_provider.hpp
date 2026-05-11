#pragma once

#include "../../application/providers/flight_provider.hpp"

class AirFranceFlightProvider : public FlightProvider
{
public:
    [[nodiscard]] std::string getName() const override
    {
        return "AirFrance";
    }

    [[nodiscard]] std::vector<std::unique_ptr<ItineraryItem>> searchReservations() const override;

    [[nodiscard]] bool reserve(Reservation *reservation) const override;

    [[nodiscard]] std::unique_ptr<ReservationProvider> clone() const override { return std::make_unique<AirFranceFlightProvider>(*this); }

    ~AirFranceFlightProvider() override = default;
};
