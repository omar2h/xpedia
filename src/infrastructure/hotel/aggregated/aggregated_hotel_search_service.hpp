#pragma once

#include <memory>
#include <vector>

#include "../../../application/interfaces/ihotel_search_service.hpp"

class AggregatedHotelSearchService : public IHotelSearchService
{
    std::vector<std::unique_ptr<IHotelSearchService>> m_services;

  public:
    explicit AggregatedHotelSearchService(std::vector<std::unique_ptr<IHotelSearchService>> services);

    Result<std::vector<HotelOffer>> searchHotels(const HotelSearchRequest& request) override;
};
