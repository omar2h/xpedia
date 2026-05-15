#include "reservation_service.hpp"
#include "../../domain/requests/reservation_request.hpp"
#include "../providers/reservation_provider.hpp"
#include "../../domain/entities/itinerary.hpp"
#include "../../domain/entities/reservation.hpp"
#include <map>
#include <stdexcept>

ReservationService::ReservationService(
    std::function<std::vector<std::unique_ptr<ReservationProvider>>(ReservationCategory)> getProviders,
    std::function<std::unique_ptr<ReservationProvider>(ReservationCategory, const std::string &)> getReservationProvider)
    : m_getProviders(std::move(getProviders)),
      m_getReservationProvider(std::move(getReservationProvider)) {}

std::vector<std::unique_ptr<ItineraryItem>> ReservationService::getAvailableReservations(
    ReservationRequest &request, RequestType requestType)
{
    std::vector<std::unique_ptr<ItineraryItem>> items;

    static const std::map<RequestType, ReservationCategory> requestTypeToCategory = {
        {RequestType::flight, ReservationCategory::flight},
        {RequestType::hotel, ReservationCategory::hotel}};

    auto it = requestTypeToCategory.find(requestType);
    if (it == requestTypeToCategory.end())
    {
        throw std::invalid_argument("Unknown RequestType");
    }
    ReservationCategory cat = it->second;

    auto providers = m_getProviders(cat);

    for (auto &provider : providers)
    {
        provider->setRequest(&request);

        std::vector<std::unique_ptr<ItineraryItem>> results = provider->searchReservations();

        items.insert(items.end(),
                     std::make_move_iterator(results.begin()),
                     std::make_move_iterator(results.end()));
    }

    return items;
}

bool ReservationService::confirmReservations(const Itinerary &currItinerary)
{
    std::unique_ptr<ReservationProvider> provider{};

    const auto &reservations = currItinerary.getReservations();

    for (const auto &res : reservations)
    {
        provider = m_getReservationProvider(res->getCategory(), res->getProviderId());

        if (!provider->reserve(res.get()))
        {
            return false;
        }
    }
    return true;
}
