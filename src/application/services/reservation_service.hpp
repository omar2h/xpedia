#pragma once

#include <functional>
#include <memory>
#include <vector>
#include <string>

#include "../../domain/entities/reservation_category.hpp"
#include "../providers/booking_provider.hpp"

class Itinerary;
class BookingProvider;

class ReservationService
{
    std::function<std::unique_ptr<BookingProvider>(ReservationCategory, const std::string &)> m_getBookingProvider;

public:
    ReservationService(
        std::function<std::unique_ptr<BookingProvider>(ReservationCategory, const std::string &)> getBookingProvider);

    [[nodiscard]] bool confirmReservations(const Itinerary &itinerary);
};
