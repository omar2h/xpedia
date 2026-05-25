#pragma once

#include "flight_search_input.hpp"
#include "../../domain/value_objects/flight_offer.hpp"

struct SelectedFlightOffer
{
    FlightSearchInput input;
    FlightOffer offer;
};
