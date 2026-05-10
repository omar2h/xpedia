#pragma once

#include "flights_manager.hpp"

class BritishAirwaysFlightsManager : public FlightsManager
{
public:
    std::string getName() const override
    {
        return "BritishAirways";
    }

    std::vector<ItineraryItem *> search_reservations() const override;

    bool reserve(Reservation *reservation) const override;

    ItineraryManager *clone() override { return new BritishAirwaysFlightsManager(*this); };

    ~BritishAirwaysFlightsManager() override = default;
};
