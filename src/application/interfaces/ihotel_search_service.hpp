#pragma once

#include <string>
#include <vector>

#include "../../domain/result.hpp"
#include "../../domain/value_objects/hotel_offer.hpp"
#include "../../domain/value_objects/hotel_search_request.hpp"

class IHotelSearchService
{
  public:
    virtual ~IHotelSearchService() = default;

    virtual Result<std::vector<HotelOffer>> searchHotels(const HotelSearchRequest& request) = 0;
};
