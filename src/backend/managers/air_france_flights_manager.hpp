#pragma once

#include "flights_manager.hpp"

class AirFranceFlightsManager : public FlightsManager
{
public:
    std::string getName() const override
    {
        return "AirFrance";
    }

    std::vector<ItineraryItem *> search_reservations() const override;

    bool reserve(Reservation *reservation) const override;

    ItineraryManager *clone() override { return new AirFranceFlightsManager(*this); };

    ~AirFranceFlightsManager() override = default;
};
