#ifndef __TURKISHFLIGHTSMANAGER_H__
#define __TURKISHFLIGHTSMANAGER_H__
#include "flightsManager.h"

class TurkishFlightsManager : public FlightsManager
{
    std::string getName() const override
    {
        return "Turkish Airlines";
    }

    std::vector<Flight> search_flights() const override;

    bool reserve_flight(const FlightReservation &reservation) const;
};
#endif // __TURKISHFLIGHTSMANAGER_H__