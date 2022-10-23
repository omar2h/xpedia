#ifndef __FLIGHTSMANAGER_H__
#define __FLIGHTSMANAGER_H__

#include "flightRequest.h"
#include "flightReservation.h"
#include "flight.h"
#include "itineraryManager.h"
#include <vector>

class FlightsManager : public ItineraryManager
{

public:
    std::vector<ItineraryItem *> search_reservations() const override = 0;

    bool reserve(Reservation *) const override = 0;

    std::string getName() const override = 0;

    ItineraryManager *Clone() override = 0;

    virtual ~FlightsManager()
    {
    }
};
#endif // __FLIGHTSMANAGER_H__