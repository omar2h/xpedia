#include "reservation_provider_factory.hpp"
#include "flight_provider_factory.hpp"
#include "hotel_provider_factory.hpp"

std::unique_ptr<ReservationProvider> RoutingReservationProviderFactory::getProvider(ReservationType type) const
{
    FlightProviderFactory flightsFactory;
    HotelProviderFactory hotelsFactory;
    if (type == ReservationType::britishAirways || type == ReservationType::airFrance)
        return flightsFactory.getProvider(type);
    else if (type == ReservationType::marriott || type == ReservationType::hilton)
        return hotelsFactory.getProvider(type);

    return nullptr;
}

std::vector<std::unique_ptr<ReservationProvider>> RoutingReservationProviderFactory::getProviders() const
{
    FlightProviderFactory flightsFactory;
    HotelProviderFactory hotelsFactory;
    auto providers = flightsFactory.getProviders();
    auto hotelProviders = hotelsFactory.getProviders();
    providers.insert(providers.end(),
                     std::make_move_iterator(hotelProviders.begin()),
                     std::make_move_iterator(hotelProviders.end()));
    return providers;
}
