#include "duffel_flight_service.hpp"
#include "parser/duffel_parser.hpp"
#include "mapper/duffel_mapper.hpp"
#include <iostream>
#include <vector>

DuffelFlightService::DuffelFlightService(const std::string &apiKey)
    : m_client(apiKey)
{
}

Result<std::vector<FlightOffer>> DuffelFlightService::searchFlights(
    const FlightSearchRequest &request)
{
    std::string raw = m_client.searchOffers(
        request.origin,
        request.destination,
        request.departureDate);

    auto parsed = m_parser.parse(raw);

    if (!parsed.errorMessage.empty())
    {
        std::cerr << "Duffel API error: " << parsed.errorMessage << "\n";
        std::cerr << "Raw response (first 300 chars): " << raw.substr(0, 300) << "\n";
        std::cerr << "Request: " << request.origin << " -> " << request.destination
                  << " on " << request.departureDate << "\n";
        return Result<std::vector<FlightOffer>>::fail(parsed.errorMessage);
    }

    auto offers = m_mapper.toFlightOffers(parsed);
    return Result<std::vector<FlightOffer>>::ok(std::move(offers));
}
