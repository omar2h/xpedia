#pragma once

#include "../../../application/interfaces/ihotel_search_service.hpp"

#include "client/liteapi_hotel_client.hpp"
#include "parser/liteapi_hotel_parser.hpp"

class LiteApiHotelService : public IHotelSearchService
{
    LiteApiHotelClient m_client;
    liteapi::LiteApiHotelParser m_parser;

public:
    explicit LiteApiHotelService(const std::string &apiKey);

    Result<std::vector<HotelOffer>> searchHotels(const HotelSearchRequest &request) override;
};