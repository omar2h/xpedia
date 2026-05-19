#pragma once

#include <string>
#include <vector>
#include "flight_offer_models.hpp"

// ---------------------------------------------------------------------------
// MockBookingAPI
//
// Mock flight-booking / search API.
//
// Responsibility: return BOOKING OFFERS (price, route, times) for a given
// route and date.  This is the layer the user interacts with when searching
// for and selecting a flight to book.
//
// In a real system this would call a GDS or airline booking API.
// For this project it returns hardcoded offers.
// ---------------------------------------------------------------------------
class MockBookingAPI
{
public:
    // Return a list of booking offers for the given route/date.
    // The `from` / `to` parameters are IATA airport codes.
    static std::vector<FlightOffer> searchOffers(
        const std::string &from,
        const std::string &to,
        const std::string &date,
        int adults = 1,
        int children = 0);

    // Stub reservation — always succeeds in mock mode.
    static bool reserve(const std::string &offerId);
};
