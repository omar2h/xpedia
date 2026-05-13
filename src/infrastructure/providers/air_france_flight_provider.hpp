#pragma once

#include "../../application/providers/reservation_provider.hpp"

class AirFranceFlightProvider : public ReservationProvider
{
public:
    [[nodiscard]] std::string getName() const override
    {
        return "AirFrance";
    }

    [[nodiscard]] std::vector<std::unique_ptr<ItineraryItem>> searchReservations() const override;

    [[nodiscard]] bool reserve(Reservation *reservation) const override;

    [[nodiscard]] std::string getCategory() const override { return "flight"; }
};
