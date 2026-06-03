#include "mock_flight_search_service.hpp"

FlightSearchResult MockFlightSearchService::searchFlights(const FlightSearchRequest& request)
{
    FlightSearchResult result;
    FlightOffer offer;
    offer.id = "MOCK_1";
    offer.airline = "EgyptAir";
    offer.origin = request.origin;
    offer.destination = request.destination;
    offer.departureTime = request.departureDate + "T10:00";
    offer.arrivalTime = request.departureDate + "T13:30";
    offer.duration = "PT3H30M";
    offer.directFlight = true;
    offer.price = 450.0;
    offer.currency = "USD";
    result.offers.push_back(offer);
    return result;
}
