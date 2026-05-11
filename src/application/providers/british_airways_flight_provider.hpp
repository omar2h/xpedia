#pragma once

#include "flight_provider.hpp"

class BritishAirwaysFlightProvider : public FlightProvider
{
public:
    std::string getName() const override
    {
        return "BritishAirways";
    }

    std::vector<std::unique_ptr<ItineraryItem>> search_reservations() const override;

    bool reserve(Reservation *reservation) const override;

    ReservationProvider *clone() override { return new BritishAirwaysFlightProvider(*this); };

    ~BritishAirwaysFlightProvider() override = default;
};
