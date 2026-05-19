#pragma once

#include "../../../application/interfaces/iflight_search_service.hpp"
#include "client/duffel_client.hpp"
#include "parser/duffel_parser.hpp"
#include "mapper/duffel_mapper.hpp"

class DuffelFlightService : public IFlightSearchService
{
    DuffelClient m_client;
    duffel::DuffelParser m_parser;
    duffel::DuffelMapper m_mapper;

public:
    explicit DuffelFlightService(const std::string &apiKey);

    Result<std::vector<FlightOffer>> searchFlights(
        const FlightSearchRequest &request) override;
};
