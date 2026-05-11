#pragma once

#include <vector>
#include <memory>
#include <functional>
#include "../../model/requests/reservation_request.hpp"
#include "../providers/reservation_provider.hpp"

class ItineraryItem;
class Itinerary;
enum class ReservationType;

class ReservationService
{
    std::function<std::vector<std::unique_ptr<ReservationProvider>>()> m_getFlightProviders;
    std::function<std::vector<std::unique_ptr<ReservationProvider>>()> m_getHotelProviders;
    std::function<std::unique_ptr<ReservationProvider>(ReservationType)> m_getReservationProvider;

public:
    ReservationService(
        std::function<std::vector<std::unique_ptr<ReservationProvider>>()> getFlightProviders,
        std::function<std::vector<std::unique_ptr<ReservationProvider>>()> getHotelProviders,
        std::function<std::unique_ptr<ReservationProvider>(ReservationType)> getReservationProvider);

    [[nodiscard]] std::vector<std::unique_ptr<ItineraryItem>> getAvailableReservations(ReservationRequest *, RequestType);

    [[nodiscard]] bool confirmReservations(const Itinerary &currItinerary);
};
