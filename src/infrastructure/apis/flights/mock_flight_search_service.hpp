#pragma once

#include <string>
#include <vector>
#include "flight_offer_models.hpp"

class MockFlightSearchService
{
public:
    FlightSearchResult
    searchFlights(const FlightSearchRequest &request);
};