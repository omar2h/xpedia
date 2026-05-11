#include "reservation_service.hpp"
#include "../providers/reservation_provider.hpp"
#include "../../model/itinerary.hpp"
#include "../../model/reservation.hpp"
#include "../../model/requests/reservation_request.hpp"

ReservationService::ReservationService(
    std::function<std::vector<std::unique_ptr<ReservationProvider>>()> getFlightProviders,
    std::function<std::vector<std::unique_ptr<ReservationProvider>>()> getHotelProviders,
    std::function<std::unique_ptr<ReservationProvider>(ReservationType)> getReservationProvider)
    : m_getFlightProviders(std::move(getFlightProviders)),
      m_getHotelProviders(std::move(getHotelProviders)),
      m_getReservationProvider(std::move(getReservationProvider)) {}

std::vector<std::unique_ptr<ItineraryItem>> ReservationService::getAvailableReservations(
    ReservationRequest *request, RequestType requestType)
{
    std::vector<std::unique_ptr<ItineraryItem>> items;
    std::vector<std::unique_ptr<ReservationProvider>> providers;

    if (requestType == RequestType::flight)
    {
        providers = m_getFlightProviders();

        for (auto &provider : providers)
        {
            provider->setRequest(request);

            std::vector<std::unique_ptr<ItineraryItem>> results = provider->searchReservations();

            items.insert(items.end(),
                         std::make_move_iterator(results.begin()),
                         std::make_move_iterator(results.end()));
        }
    }
    else if (requestType == RequestType::hotel)
    {
        providers = m_getHotelProviders();

        for (auto &provider : providers)
        {
            provider->setRequest(request);

            std::vector<std::unique_ptr<ItineraryItem>> results = provider->searchReservations();

            items.insert(items.end(),
                         std::make_move_iterator(results.begin()),
                         std::make_move_iterator(results.end()));
        }
    }

    return items;
}

bool ReservationService::confirmReservations(const Itinerary &currItinerary)
{
    std::unique_ptr<ReservationProvider> provider{};

    const auto &reservations = currItinerary.getReservations();

    for (const auto &res : reservations)
    {
        provider = m_getReservationProvider(res->getType());

        if (!provider->reserve(res.get()))
        {
            return false;
        }
    }
    return true;
}
