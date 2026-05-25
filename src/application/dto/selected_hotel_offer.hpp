#pragma once

#include "hotel_search_input.hpp"
#include "../../domain/value_objects/hotel_offer.hpp"

struct SelectedHotelOffer
{
    HotelSearchInput input;
    HotelOffer offer;
};
