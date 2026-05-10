#include "itinerary_manager_factory.hpp"
#include "flights_manager_factory.hpp"
#include "hotels_manager_factory.hpp"

std::unique_ptr<ItineraryManager> ItineraryManagerFactory::getManager(ReservationType type)
{
    FlightsManagerFactory flightsFactory;
    HotelsManagerFactory hotelsFactory;
    if (type == ReservationType::britishAirways || type == ReservationType::airFrance)
        return flightsFactory.getManager(type);
    else if (type == ReservationType::marriott || type == ReservationType::hilton)
        return hotelsFactory.getManager(type);
}
