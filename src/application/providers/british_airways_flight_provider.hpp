#pragma once

#include "flight_provider.hpp"

class BritishAirwaysFlightProvider : public FlightProvider
{
public:
    std::string getName() const override
    {
        return "BritishAirways";
    }

    std::vector<std::unique_ptr<ItineraryItem>> searchReservations() const override;

    bool reserve(Reservation *reservation) const override;

    std::unique_ptr<ReservationProvider> clone() const override { return std::make_unique<BritishAirwaysFlightProvider>(*this); }

    ~BritishAirwaysFlightProvider() override = default;
};
