#pragma once

#include "../formatters/reservation_formatter.hpp"
#include "../view_models/view_models.hpp"

inline ItineraryViewModel toItineraryViewModel(const Itinerary& itinerary)
{
    return {formatItinerarySummary(itinerary)};
}
