#pragma once

#include "../../interfaces/ihotel_search_service.hpp"

#include "../../../domain/result.hpp"
#include "../../../domain/value_objects/hotel_offer.hpp"

#include "../../dto/hotel_search_input.hpp"

class SearchHotelsUseCase
{
    IHotelSearchService& m_hotelService;

  public:
    explicit SearchHotelsUseCase(IHotelSearchService& hotelService);
    Result<std::vector<HotelOffer>> execute(const HotelSearchInput& input);
};
