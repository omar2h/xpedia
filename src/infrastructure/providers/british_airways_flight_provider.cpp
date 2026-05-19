#include "british_airways_flight_provider.hpp"
#include "../apis/flights/mock_flight_search_service.hpp"
#include "../../domain/entities/flight.hpp"
#include "../../domain/requests/flight_request.hpp"

std::vector<std::unique_ptr<ItineraryItem>> BritishAirwaysFlightProvider::searchReservations() const
{
    auto req = getRequest();
    const FlightRequest &request = dynamic_cast<const FlightRequest &>(*req);

    MockFlightSearchService searchService;
    FlightSearchRequest searchReq;
    searchReq.origin = request.getFromCity();
    searchReq.destination = request.getToCity();
    searchReq.departureDate = request.getDate();
    searchReq.adults = request.getAdults();
    searchReq.children = request.getChildren();

    auto result = searchService.searchFlights(searchReq);

    std::vector<std::unique_ptr<ItineraryItem>> results;

    for (const auto &offer : result.offers)
    {
        Flight flight;
        flight.setCategory(ReservationCategory::flight);
        flight.setProviderId("british_airways");
        flight.setRequestType(RequestType::flight);
        flight.setAirline(offer.airline);
        flight.setDate(offer.departureTime);
        flight.setTotalCost(offer.price);
        results.push_back(flight.clone());
    }

    return results;
}

bool BritishAirwaysFlightProvider::reserve(Reservation * /*reservation*/) const
{
    // Reservation is a mock operation (internal only, no external booking API).
    return true;
}
