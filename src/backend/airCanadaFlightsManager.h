#ifndef __AIRCANADAFLIGHTSMANAGER_H__
#define __AIRCANADAFLIGHTSMANAGER_H__
#include "flightsManager.h"

class AirCanadaFlightsManager : public FlightsManager
{
public:
    std::string getName() const override
    {
        return "AirCanada";
    }

    std::vector<ItineraryItem *> search_reservations() const override;

    bool reserve(Reservation *reservation) const override;

    ItineraryManager *Clone() override { return new AirCanadaFlightsManager(*this); };

    ~AirCanadaFlightsManager() override
    {
    }
};
#endif // __AIRCANADAFLIGHTSMANAGER_H__