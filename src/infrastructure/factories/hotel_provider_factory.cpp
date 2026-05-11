#include "hotel_provider_factory.hpp"
#include "providers/marriott_hotel_provider.hpp"
#include "providers/hilton_hotel_provider.hpp"
std::unique_ptr<ReservationProvider> HotelProviderFactory::getProvider(ReservationType type)
{
    if (type == ReservationType::marriott)
        return std::make_unique<MarriottHotelProvider>();
    else if (type == ReservationType::hilton)
        return std::make_unique<HiltonHotelProvider>();

    return nullptr;
}

std::vector<std::unique_ptr<ReservationProvider>> HotelProviderFactory::getProviders()
{
    std::vector<std::unique_ptr<ReservationProvider>> providers;
    providers.push_back(std::make_unique<MarriottHotelProvider>());
    providers.push_back(std::make_unique<HiltonHotelProvider>());
    return providers;
}
