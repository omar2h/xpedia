#include "liteapi_hotel_parser.hpp"
#include "json.hpp"
#include <iostream>
#include <unordered_map>

using json = nlohmann::json;

namespace liteapi
{

Result<LiteApiHotelResponse> LiteApiHotelParser::parse(const std::string& raw)
{
    LiteApiHotelResponse response;

    try
    {
        auto j = json::parse(raw);

        if (!j.contains("data") || j["data"].empty())
            return Result<LiteApiHotelResponse>::failure("No hotel offers found");

        std::unordered_map<std::string, std::string> hotelNames;

        for (const auto& item : j["data"])
        {
            std::string hotelId = item.value("hotelId", "");

            auto it = hotelNames.find(hotelId);
            std::string hotelName = (it != hotelNames.end()) ? it->second : item.value("hotelName", "");

            if (!item.contains("roomTypes"))
                continue;

            for (const auto& roomType : item["roomTypes"])
            {
                if (!roomType.contains("rates"))
                    continue;

                for (const auto& rate : roomType["rates"])
                {
                    LiteApiHotel hotel;

                    hotel.hotelId = hotelId;
                    hotel.hotelName = hotelName;
                    hotel.roomName = rate.value("name", "");
                    hotel.rateId = rate.value("rateId", "");
                    hotel.boardType = rate.value("boardType", rate.value("boardName", ""));

                    if (rate.contains("cancellationPolicies") && rate["cancellationPolicies"].contains("refundableTag"))
                    {
                        std::string tag = rate["cancellationPolicies"]["refundableTag"].get<std::string>();
                        hotel.refundable = (tag == "RFN" || tag == "REF");
                    }

                    if (rate.contains("retailRate") && rate["retailRate"].contains("total") &&
                        !rate["retailRate"]["total"].empty())
                    {
                        const auto& total = rate["retailRate"]["total"][0];
                        hotel.price = total.value("amount", 0.0);
                        hotel.currency = total.value("currency", "USD");
                    }

                    response.hotels.push_back(hotel);
                }
            }
        }

        if (response.hotels.empty())
            return Result<LiteApiHotelResponse>::failure("No hotel offers found");

        return Result<LiteApiHotelResponse>::success(response);
    }
    catch (const std::exception& e)
    {
        return Result<LiteApiHotelResponse>::failure(e.what());
    }
}

} // namespace liteapi
