#include "reservation_provider_factory.hpp"
#include "flight_provider_factory.hpp"
#include "hotel_provider_factory.hpp"

std::unique_ptr<ReservationProvider> RoutingReservationProviderFactory::getProvider(ReservationCategory category, const std::string &providerId) const
{
    FlightProviderFactory flightsFactory;
    HotelProviderFactory hotelsFactory;
    if (category == ReservationCategory::flight)
        return flightsFactory.getProvider(providerId);
    else
        return hotelsFactory.getProvider(providerId);
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
