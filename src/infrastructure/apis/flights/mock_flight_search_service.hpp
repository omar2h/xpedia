#pragma once

#include "flight_offer_models.hpp"
#include <string>
#include <vector>

class MockFlightSearchService
{
  public:
    FlightSearchResult searchFlights(const FlightSearchRequest& request);
};