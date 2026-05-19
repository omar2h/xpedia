#pragma once

#include "dto/hotel_search_input.hpp"

class IView;
class IInput;

class HotelSearchForm
{
public:
    static HotelSearchInput collect(IView& view, IInput& input);
};
