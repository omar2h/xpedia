#include "duffel_hotel_service.hpp"

DuffelHotelService::DuffelHotelService(const std::string &apiKey)
    : m_client(apiKey)
{
}

Result<std::vector<HotelOffer>> DuffelHotelService::searchHotels(const HotelSearchRequest &request)
{
    auto response = m_client.searchHotels(request);

    if (!response.isSuccess())
    {
        return Result<std::vector<HotelOffer>>::failure(response.error());
    }

    auto parsed = m_parser.parse(response.value());
    if (!parsed.isSuccess())
    {
        return Result<std::vector<HotelOffer>>::failure(parsed.error());
    }

    auto offers = m_mapper.map(parsed.value());
    return Result<std::vector<HotelOffer>>::success(std::move(offers));
}
