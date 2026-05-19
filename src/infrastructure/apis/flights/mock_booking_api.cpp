#include "mock_booking_api.hpp"
#include "../../../third_party/json.hpp"
#include <algorithm>
#include <random>

using json = nlohmann::json;

// ---------------------------------------------------------------------------
// MockBookingAPI — hardcoded offers per route
// ---------------------------------------------------------------------------

std::vector<FlightOffer> MockBookingAPI::searchOffers(
    const std::string &from, const std::string &to,
    const std::string &date, int /*adults*/, int /*children*/)
{
    // Deterministic mock data keyed by route so the same route always
    // returns the same offers (no network call, no randomness needed).
    std::vector<FlightOffer> offers;

    // ---- ATL → YYZ ----
    if (from == "ATL" && to == "YYZ")
    {
        FlightOffer offer1;
        offer1.id = "UA8569";
        offer1.airline = "United Airlines";
        offer1.origin = "ATL";
        offer1.destination = "YYZ";
        offer1.departureTime = "2026-05-15T07:00:00+00:00";
        offer1.arrivalTime = "2026-05-15T09:21:00+00:00";
        offer1.duration = "PT2H21M";
        offer1.directFlight = true;
        offer1.price = 420.0;
        offer1.currency = "USD";
        offers.push_back(offer1);

        FlightOffer offer2;
        offer2.id = "AC1222";
        offer2.airline = "Air Canada";
        offer2.origin = "ATL";
        offer2.destination = "YYZ";
        offer2.departureTime = "2026-05-15T07:30:00+00:00";
        offer2.arrivalTime = "2026-05-15T09:50:00+00:00";
        offer2.duration = "PT2H20M";
        offer2.directFlight = true;
        offer2.price = 380.0;
        offer2.currency = "USD";
        offers.push_back(offer2);
    }
    // ---- ATL → IAH ----
    else if (from == "ATL" && to == "IAH")
    {
        FlightOffer offer;
        offer.id = "NZ6330";
        offer.airline = "Air New Zealand";
        offer.origin = "ATL";
        offer.destination = "IAH";
        offer.departureTime = "2026-05-15T07:00:00+00:00";
        offer.arrivalTime = "2026-05-15T08:21:00+00:00";
        offer.duration = "PT1H21M";
        offer.directFlight = true;
        offer.price = 310.0;
        offer.currency = "USD";
        offers.push_back(offer);
    }
    // ---- ATL → LAX ----
    else if (from == "ATL" && to == "LAX")
    {
        FlightOffer offer1;
        offer1.id = "LA7938";
        offer1.airline = "LATAM Airlines";
        offer1.origin = "ATL";
        offer1.destination = "LAX";
        offer1.departureTime = "2026-05-15T07:00:00+00:00";
        offer1.arrivalTime = "2026-05-15T08:50:00+00:00";
        offer1.duration = "PT2H50M";
        offer1.directFlight = true;
        offer1.price = 520.0;
        offer1.currency = "USD";
        offers.push_back(offer1);

        FlightOffer offer2;
        offer2.id = "KE6285";
        offer2.airline = "Korean Air";
        offer2.origin = "ATL";
        offer2.destination = "LAX";
        offer2.departureTime = "2026-05-15T07:00:00+00:00";
        offer2.arrivalTime = "2026-05-15T08:50:00+00:00";
        offer2.duration = "PT2H50M";
        offer2.directFlight = true;
        offer2.price = 540.0;
        offer2.currency = "USD";
        offers.push_back(offer2);

        FlightOffer offer3;
        offer3.id = "AM3353";
        offer3.airline = "Aeromexico";
        offer3.origin = "ATL";
        offer3.destination = "LAX";
        offer3.departureTime = "2026-05-15T07:00:00+00:00";
        offer3.arrivalTime = "2026-05-15T08:50:00+00:00";
        offer3.duration = "PT2H50M";
        offer3.directFlight = true;
        offer3.price = 490.0;
        offer3.currency = "USD";
        offers.push_back(offer3);
    }
    // ---- ATL → ORD ----
    else if (from == "ATL" && to == "ORD")
    {
        FlightOffer offer;
        offer.id = "RJ7267";
        offer.airline = "Royal Jordanian";
        offer.origin = "ATL";
        offer.destination = "ORD";
        offer.departureTime = "2026-05-15T06:52:00+00:00";
        offer.arrivalTime = "2026-05-15T08:15:00+00:00";
        offer.duration = "PT1H23M";
        offer.directFlight = true;
        offer.price = 290.0;
        offer.currency = "USD";
        offers.push_back(offer);
    }
    // ---- Generic fallback for any other route ----
    else
    {
        FlightOffer offer1;
        offer1.id = "XX100";
        offer1.airline = from + " Airways";
        offer1.origin = from;
        offer1.destination = to;
        offer1.departureTime = date + "T08:00:00+00:00";
        offer1.arrivalTime = date + "T10:00:00+00:00";
        offer1.duration = "PT2H00M";
        offer1.directFlight = true;
        offer1.price = 350.0;
        offer1.currency = "USD";
        offers.push_back(offer1);

        FlightOffer offer2;
        offer2.id = "XX200";
        offer2.airline = to + " Express";
        offer2.origin = from;
        offer2.destination = to;
        offer2.departureTime = date + "T12:00:00+00:00";
        offer2.arrivalTime = date + "T14:00:00+00:00";
        offer2.duration = "PT2H00M";
        offer2.directFlight = true;
        offer2.price = 400.0;
        offer2.currency = "USD";
        offers.push_back(offer2);
    }

    return offers;
}

bool MockBookingAPI::reserve(const std::string & /*offerId*/)
{
    // Mock reservation always succeeds.
    return true;
}
