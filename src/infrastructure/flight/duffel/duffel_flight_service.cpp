#include "duffel_flight_service.hpp"

DuffelFlightService::DuffelFlightService(const std::string& apiKey) : m_client(apiKey) {}

Result<std::vector<FlightOffer>> DuffelFlightService::searchFlights(const FlightSearchRequest& request)
{
    auto response = m_client.searchFlights(request);

    if (!response.isSuccess())
    {
        return Result<std::vector<FlightOffer>>::failure(response.error());
    }

    auto parsed = m_parser.parse(response.value());
    if (!parsed.isSuccess())
    {
        return Result<std::vector<FlightOffer>>::failure(parsed.error());
    }
    auto offers = m_mapper.map(parsed.value());
    return Result<std::vector<FlightOffer>>::success(std::move(offers));
}