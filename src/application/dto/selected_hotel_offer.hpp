#pragma once

#include "../../domain/value_objects/hotel_offer.hpp"
#include "hotel_search_input.hpp"

struct SelectedHotelOffer
{
    HotelSearchInput input;
    HotelOffer offer;
};
