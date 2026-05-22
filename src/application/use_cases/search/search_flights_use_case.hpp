#pragma once

#include "../../interfaces/iflight_search_service.hpp"

#include "../../../domain/result.hpp"
#include "../../../domain/value_objects/flight_offer.hpp"

#include "../../dto/flight_search_input.hpp"

class SearchFlightsUseCase
{
    IFlightSearchService &m_flightService;

public:
    explicit SearchFlightsUseCase(IFlightSearchService &flightService);
    Result<std::vector<FlightOffer>> execute(const FlightSearchInput &input);
};