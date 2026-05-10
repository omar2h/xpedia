#pragma once

#include "../../model/requests/hotel_request.hpp"
#include "../../model/reservations/hotel_reservation.hpp"
#include "itinerary_manager.hpp"
#include <vector>
class HotelsManager : public ItineraryManager
{
public:
    std::vector<ItineraryItem *> search_reservations() const override = 0;

    bool reserve(Reservation *) const override = 0;

    std::string getName() const override = 0;

    ItineraryManager *clone() override = 0;

    ~HotelsManager() override = default;
};
