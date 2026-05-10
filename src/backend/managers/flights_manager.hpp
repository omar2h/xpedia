#pragma once

#include "../../model/requests/flight_request.hpp"
#include "../../model/reservations/flight_reservation.hpp"
#include "../../model/flight.hpp"
#include "itinerary_manager.hpp"
#include <vector>

class FlightsManager : public ItineraryManager
{

public:
    std::vector<ItineraryItem *> search_reservations() const override = 0;

    bool reserve(Reservation *) const override = 0;

    std::string getName() const override = 0;

    ItineraryManager *clone() override = 0;

    virtual ~FlightsManager()
    {
    }
};
