#ifndef __AIRFRANCEFLIGHTSMANAGER_H__
#define __AIRFRANCEFLIGHTSMANAGER_H__
#include "flightsManager.h"

class AirFranceFlightsManager : public FlightsManager
{
public:
    std::string getName() const override
    {
        return "AirFrance";
    }

    std::vector<ItineraryItem *> search_reservations() const override;

    bool reserve(Reservation *reservation) const override;

    ItineraryManager *Clone() override { return new AirFranceFlightsManager(*this); };

    ~AirFranceFlightsManager() override = default;
};
#endif // __AIRFRANCEFLIGHTSMANAGER_H__