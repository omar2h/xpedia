#pragma once

#include "../view_models/view_models.hpp"
#include "../formatters/reservation_formatter.hpp"

inline SearchResultViewModel toSearchResultViewModel(const ItineraryItem& item)
{
    return {formatItineraryItem(item)};
}
