#pragma once

#include "../view_models/view_models.hpp"
#include "../formatters/reservation_formatter.hpp"

inline ItineraryViewModel toItineraryViewModel(const Itinerary& itinerary)
{
    return {formatItinerarySummary(itinerary)};
}
