#pragma once

#include "../../../application/interfaces/ihotel_search_service.hpp"

#include "client/duffel_hotel_client.hpp"
#include "mapper/duffel_hotel_mapper.hpp"
#include "parser/duffel_hotel_parser.hpp"

class DuffelHotelService : public IHotelSearchService
{
    DuffelHotelClient m_client;
    duffel::DuffelHotelParser m_parser;
    duffel::DuffelHotelMapper m_mapper;

public:
    explicit DuffelHotelService(const std::string &apiKey);

    Result<std::vector<HotelOffer>> searchHotels(const HotelSearchRequest &request) override;
};
