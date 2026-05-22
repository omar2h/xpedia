#pragma once

#include "../../application/use_cases/search/search_flights_use_case.hpp"

class IView;
class IInput;
class User;

class FlightSearchPresenter
{
    IView &m_view;
    IInput &m_input;
    SearchFlightsUseCase &m_useCase;

public:
    FlightSearchPresenter(IView &view, IInput &input, SearchFlightsUseCase &useCase);

    void run(User &user);
};