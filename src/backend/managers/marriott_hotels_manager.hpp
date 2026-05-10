#pragma once

#include "hotels_manager.hpp"

class MarriottHotelsManager : public HotelsManager
{
public:
    std::vector<ItineraryItem *> search_reservations() const override;

    bool reserve(Reservation *) const override;

    std::string getName() const override;

    ItineraryManager *clone() override;
};
