#pragma once

#include <memory>

#include "application/use_cases/search/search_flights_use_case.hpp"

#include "presentation/presenters/flight_search_presenter.hpp"

#include "infrastructure/flight/aggregated/aggregated_flight_search_service.hpp"

class IView;
class IInput;

struct FlightModule
{
    std::unique_ptr<AggregatedFlightSearchService> service;
    std::unique_ptr<SearchFlightsUseCase> useCase;
    std::unique_ptr<FlightSearchPresenter> presenter;
};

FlightModule createFlightModule(IView& view, IInput& input);