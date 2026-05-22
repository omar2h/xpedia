#pragma once

#include <functional>
#include <memory>
#include <vector>
#include <string>

#include "../../domain/entities/reservation_category.hpp"
#include "../providers/hotel_search_provider.hpp"
#include "../providers/booking_provider.hpp"

class Itinerary;
class ItineraryItem;
class FlightSearchRequest;
class HotelSearchRequest;
class BookingProvider;

class ReservationService
{
    std::function<std::vector<std::unique_ptr<HotelSearchProvider>>()> m_getHotelProviders;
    std::function<std::unique_ptr<BookingProvider>(ReservationCategory, const std::string &)> m_getBookingProvider;

public:
    ReservationService(
        std::function<std::vector<std::unique_ptr<HotelSearchProvider>>()> getHotelProviders,
        std::function<std::unique_ptr<BookingProvider>(ReservationCategory, const std::string &)> getBookingProvider);

    std::vector<std::unique_ptr<ItineraryItem>> searchHotels(HotelSearchRequest &request);

    [[nodiscard]] bool confirmReservations(const Itinerary &itinerary);
};
