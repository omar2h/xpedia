#pragma once

#include <string>
#include <vector>

namespace liteapi
{

    struct LiteApiRateDTO
    {
        std::string roomName;
        double price{};
        std::string currency;
        std::string boardName;
        bool refundable{};
    };

    struct LiteApiHotelDTO
    {
        std::string hotelId;
        std::string hotelName;
        std::vector<LiteApiRateDTO> rates;
    };

    struct LiteApiSearchResponseDTO
    {
        std::vector<LiteApiHotelDTO> hotels;
    };

    struct LiteApiHotel
    {
        std::string hotelId;
        std::string hotelName;

        std::string roomName;
        std::string boardType;
        std::string rateId;

        double price = 0.0;

        std::string currency;

        bool refundable = false;
    };
    struct LiteApiHotelResponse
    {
        std::vector<LiteApiHotel> hotels;
    };

}