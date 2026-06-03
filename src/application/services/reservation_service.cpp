#include "reservation_service.hpp"
#include "../../domain/entities/itinerary.hpp"

#include <utility>

ReservationService::ReservationService(
    std::function<std::unique_ptr<BookingProvider>(ReservationCategory, const std::string&)> getBookingProvider)
    : m_getBookingProvider(std::move(getBookingProvider))
{
}

bool ReservationService::confirmReservations(const Itinerary& itinerary)
{
    const auto& reservations = itinerary.getReservations();

    for (const auto& res : reservations)
    {
        auto provider = m_getBookingProvider(res->getCategory(), res->getProviderId());

        if (!provider->reserve(*res))
        {
            return false;
        }
    }

    return true;
}
