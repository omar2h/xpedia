#pragma once

#include "dto/flight_search_input.hpp"

class IView;
class IInput;

class FlightSearchForm
{
public:
    static FlightSearchInput collect(IView &view, IInput &input);
};
