#include "reservation_provider_factory.hpp"
#include "flight_provider_factory.hpp"
#include "hotel_provider_factory.hpp"

std::unique_ptr<ReservationProvider> ReservationProviderFactory::getProvider(ReservationType type)
{
    FlightProviderFactory flightsFactory;
    HotelProviderFactory hotelsFactory;
    if (type == ReservationType::britishAirways || type == ReservationType::airFrance)
        return flightsFactory.getProvider(type);
    else if (type == ReservationType::marriott || type == ReservationType::hilton)
        return hotelsFactory.getProvider(type);

    return nullptr;
}
