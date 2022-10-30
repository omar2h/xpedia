#ifndef __BRITISHAIRWAYSFLIGHTSMANAGER_H__
#define __BRITISHAIRWAYSFLIGHTSMANAGER_H__
#include "flightsManager.h"

class BritishAirwaysFlightsManager : public FlightsManager
{
public:
    std::string getName() const override
    {
        return "BritishAirways";
    }

    std::vector<ItineraryItem *> search_reservations() const override;

    bool reserve(Reservation *reservation) const override;

    ItineraryManager *Clone() override { return new BritishAirwaysFlightsManager(*this); };

    ~BritishAirwaysFlightsManager() override = default;
};
#endif // __BRITISHAIRWAYSFLIGHTSMANAGER_H__