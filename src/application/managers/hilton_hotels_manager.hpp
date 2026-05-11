#pragma once

#include "hotels_manager.hpp"

class HiltonHotelsManager : public HotelsManager
{
public:
    std::vector<std::unique_ptr<ItineraryItem>> search_reservations() const override;

    bool reserve(Reservation *) const override;

    std::string getName() const override;

    ItineraryManager *clone() override;

    ~HiltonHotelsManager() override = default;
};
