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

    ReservationProvider *clone() override { return new AirFranceFlightProvider(*this); };

    ~AirFranceFlightProvider() override = default;
};
