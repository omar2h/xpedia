#pragma once

#include "../formatters/reservation_formatter.hpp"
#include "../view_models/view_models.hpp"

inline SearchResultViewModel toSearchResultViewModel(const ItineraryItem& item)
{
    return {formatItineraryItem(item)};
}
