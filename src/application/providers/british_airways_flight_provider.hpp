#pragma once

#include "flight_provider.hpp"

class BritishAirwaysFlightProvider : public FlightProvider
{
public:
    [[nodiscard]] std::string getName() const override
    {
        return "BritishAirways";
    }

    [[nodiscard]] std::vector<std::unique_ptr<ItineraryItem>> searchReservations() const override;

    [[nodiscard]] bool reserve(Reservation *reservation) const override;

    [[nodiscard]] std::unique_ptr<ReservationProvider> clone() const override { return std::make_unique<BritishAirwaysFlightProvider>(*this); }

    ~BritishAirwaysFlightProvider() override = default;
};
