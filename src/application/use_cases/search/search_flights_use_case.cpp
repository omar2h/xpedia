#include "search_flights_use_case.hpp"

SearchFlightsUseCase::SearchFlightsUseCase(IFlightSearchService& flightService) : m_flightService(flightService) {}

Result<std::vector<FlightOffer>> SearchFlightsUseCase::execute(const FlightSearchInput& input)
{
    FlightSearchRequest request;

    request.origin = input.origin;
    request.destination = input.destination;
    request.departureDate = input.departureDate;
    request.adults = input.adults;

    return m_flightService.searchFlights(request);
}