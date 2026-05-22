#include "reservation_service.hpp"
#include "../../domain/entities/itinerary.hpp"
#include "../../domain/entities/itinerary_item.hpp"
#include <iterator>
#include <stdexcept>

ReservationService::ReservationService(
    std::function<std::vector<std::unique_ptr<HotelSearchProvider>>()> getHotelProviders,
    std::function<std::unique_ptr<BookingProvider>(ReservationCategory, const std::string &)> getBookingProvider)

    : m_getHotelProviders(std::move(getHotelProviders)),
      m_getBookingProvider(std::move(getBookingProvider))
{
}

std::vector<std::unique_ptr<ItineraryItem>>
ReservationService::searchHotels(HotelSearchRequest &request)
{
    std::vector<std::unique_ptr<ItineraryItem>> items;

    auto providers = m_getHotelProviders();

    for (auto &provider : providers)
    {
        auto results = provider->searchHotels(request);

        items.insert(
            items.end(),
            std::make_move_iterator(results.begin()),
            std::make_move_iterator(results.end()));
    }

    return items;
}

bool ReservationService::confirmReservations(const Itinerary &itinerary)
{
    const auto &reservations = itinerary.getReservations();

    for (const auto &res : reservations)
    {
        auto provider = m_getBookingProvider(res->getCategory(), res->getProviderId());

        if (!provider->reserve(*res))
        {
            return false;
        }
    }

    return true;
}
