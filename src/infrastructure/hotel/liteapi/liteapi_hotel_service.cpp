#include "liteapi_hotel_service.hpp"
#include <iostream>
#include <unordered_map>

LiteApiHotelService::LiteApiHotelService(const std::string& apiKey) : m_client(apiKey) {}

Result<std::vector<HotelOffer>> LiteApiHotelService::searchHotels(const HotelSearchRequest& request)
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

    std::unordered_map<std::string, HotelOffer> hotelMap;
    std::vector<std::string> hotelOrder;

    for (const auto& hotel : parsed.value().hotels)
    {
        auto it = hotelMap.find(hotel.hotelId);

        if (it == hotelMap.end())
        {
            HotelOffer offer;

            offer.providerId = "liteapi";
            offer.accommodationId = hotel.hotelId;
            offer.accommodationName = hotel.hotelName;
            offer.totalPrice = 0.0;
            offer.currency = hotel.currency;

            hotelMap[hotel.hotelId] = std::move(offer);
            hotelOrder.push_back(hotel.hotelId);
        }

        HotelRoomOffer room;

        room.roomName = hotel.roomName;
        room.rateId = hotel.rateId;
        room.totalAmount = hotel.price;
        room.totalCurrency = hotel.currency;
        room.boardType = hotel.boardType;
        room.refundable = hotel.refundable;

        hotelMap[hotel.hotelId].roomOffers.push_back(std::move(room));
    }

    std::vector<HotelOffer> offers;

    for (const auto& id : hotelOrder)
    {
        auto& offer = hotelMap[id];

        if (!offer.roomOffers.empty())
        {
            offer.totalPrice = offer.roomOffers[0].totalAmount;
            offer.currency = offer.roomOffers[0].totalCurrency;
        }

        offers.push_back(std::move(offer));
    }

    return Result<std::vector<HotelOffer>>::success(std::move(offers));
}