#include "itineraryManagerFactory.h"
#include "flightsManagerFactory.h"
#include "hotelsManagerFactory.h"

ItineraryManager *ItineraryManagerFactory::getManager(ReservationType type)
{
    FlightsManagerFactory flightsFactory;
    HotelsManagerFactory hotelsFactory;
    if (type == ReservationType::britishAirways || type == ReservationType::airFrance)
        return flightsFactory.getManager(type);
    else if (type == ReservationType::marriott || type == ReservationType::hilton)
        return hotelsFactory.getManager(type);
}
