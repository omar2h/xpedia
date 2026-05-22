#pragma once

#include <memory>
#include <vector>

#include "../../../application/interfaces/iflight_search_service.hpp"

class AggregatedFlightSearchService : public IFlightSearchService
{
    std::vector<
        std::unique_ptr<IFlightSearchService>>
        m_services;

public:
    explicit AggregatedFlightSearchService(std::vector<std::unique_ptr<IFlightSearchService>> services);

    Result<std::vector<FlightOffer>> searchFlights(const FlightSearchRequest &request) override;
};