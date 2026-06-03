#pragma once

#include "../../domain/value_objects/flight_offer.hpp"
#include "flight_search_input.hpp"

struct SelectedFlightOffer
{
    FlightSearchInput input;
    FlightOffer offer;
};
