#pragma once

#include "hotels_manager.hpp"

class HiltonHotelsManager : public HotelsManager
{
public:
    std::vector<ItineraryItem *> search_reservations() const override;

    bool reserve(Reservation *) const override;

    std::string getName() const override;

    ItineraryManager *Clone() override;

    ~HiltonHotelsManager() override = default;
};
