#ifndef __TURKISHFLIGHTSMANAGER_H__
#define __TURKISHFLIGHTSMANAGER_H__
#include "flightsManager.h"

class TurkishFlightsManager : public FlightsManager
{
public:
    std::string getName() const override
    {
        return "Turkish";
    }

    std::vector<ItineraryItem *> search_reservations() const override;

    bool reserve(Reservation *reservation) const override;

    ItineraryManager *Clone() override { return new TurkishFlightsManager(*this); };

    ~TurkishFlightsManager() override
    {
    }
};
#endif // __TURKISHFLIGHTSMANAGER_H__