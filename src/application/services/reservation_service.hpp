#pragma once

#include <functional>
#include <memory>
#include <vector>
#include <string>

#include "../../domain/entities/reservation_category.hpp"

class Itinerary;
class ItineraryItem;
class ReservationProvider;
class ReservationRequest;
enum class RequestType;

class ReservationService
{
    std::function<std::vector<std::unique_ptr<ReservationProvider>>()> m_getFlightProviders;
    std::function<std::vector<std::unique_ptr<ReservationProvider>>()> m_getHotelProviders;
    std::function<std::unique_ptr<ReservationProvider>(ReservationCategory, const std::string &)> m_getReservationProvider;

public:
    ReservationService(
        std::function<std::vector<std::unique_ptr<ReservationProvider>>()> getFlightProviders,
        std::function<std::vector<std::unique_ptr<ReservationProvider>>()> getHotelProviders,
        std::function<std::unique_ptr<ReservationProvider>(ReservationCategory, const std::string &)> getReservationProvider);

    [[nodiscard]] std::vector<std::unique_ptr<ItineraryItem>> getAvailableReservations(
        ReservationRequest *request, RequestType requestType);

    [[nodiscard]] bool confirmReservations(const Itinerary &currItinerary);
};
