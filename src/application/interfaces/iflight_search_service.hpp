#pragma once

#include <string>
#include <vector>

#include "../../domain/value_objects/flight_offer.hpp"
#include "../../domain/value_objects/flight_search_request.hpp"
#include "../../domain/result.hpp"

class IFlightSearchService
{
public:
    virtual ~IFlightSearchService() = default;

    virtual Result<std::vector<FlightOffer>> searchFlights(
        const FlightSearchRequest &request) = 0;
};
