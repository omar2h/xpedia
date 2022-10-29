#include "itineraryManagerFactory.h"
#include "flightsManagerFactory.h"

ItineraryManager *ItineraryManagerFactory::getManager(ReservationType type)
{
    FlightsManagerFactory factory;
    if (type == ReservationType::aircanada || type == ReservationType::turkish)
        return factory.getManager(type);
    return {};
}
