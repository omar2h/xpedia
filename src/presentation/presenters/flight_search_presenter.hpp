#pragma once

#include <optional>

#include "application/dto/selected_flight_offer.hpp"
#include "../../application/use_cases/search/search_flights_use_case.hpp"

class IView;
class IInput;

class FlightSearchPresenter
{
    IView &m_view;
    IInput &m_input;
    SearchFlightsUseCase &m_useCase;

public:
    FlightSearchPresenter(IView &view, IInput &input, SearchFlightsUseCase &useCase);

    std::optional<SelectedFlightOffer> searchAndSelect();
};
