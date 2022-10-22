#ifndef __AIRCANADAFLIGHTSMANAGER_H__
#define __AIRCANADAFLIGHTSMANAGER_H__
#include "flightsManager.h"

class AirCanadaFlightsManager : public FlightsManager
{
public:
    std::string getName() const override
    {
        return "AirCanada Airlines";
    }

    std::vector<Flight> search_flights() const override;

    bool reserve_flight(const FlightReservation &reservation) const;

    ~AirCanadaFlightsManager() override
    {
    }
};
#endif // __AIRCANADAFLIGHTSMANAGER_H__