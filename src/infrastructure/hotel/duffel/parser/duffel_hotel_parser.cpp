#include "duffel_hotel_parser.hpp"

#include "../dto/duffel_hotel_dtos.hpp"
#include "../../../flight/duffel/utils/json_utils.hpp"

using json = nlohmann::json;
using json_utils::safeValue;

namespace duffel
{

    static DuffelHotelCancellationTimelineDTO parseCancellationTimeline(const json &j)
    {
        DuffelHotelCancellationTimelineDTO dto;
        dto.before = safeValue<std::string>(j, "before");
        dto.refundAmount = safeValue<std::string>(j, "refund_amount");
        dto.currency = safeValue<std::string>(j, "currency");
        return dto;
    }

    static DuffelHotelConditionDTO parseCondition(const json &j)
    {
        DuffelHotelConditionDTO dto;
        dto.title = safeValue<std::string>(j, "title");
        dto.description = safeValue<std::string>(j, "description");
        return dto;
    }

    static DuffelHotelRateDTO parseRate(const json &j)
    {
        DuffelHotelRateDTO dto;
        dto.id = safeValue<std::string>(j, "id");
        dto.name = safeValue<std::string>(j, "name");
        dto.description = safeValue<std::string>(j, "description");
        dto.totalAmount = safeValue<std::string>(j, "total_amount");
        dto.totalCurrency = safeValue<std::string>(j, "total_currency");
        dto.baseAmount = safeValue<std::string>(j, "base_amount");
        dto.baseCurrency = safeValue<std::string>(j, "base_currency");
        dto.taxAmount = safeValue<std::string>(j, "tax_amount");
        dto.taxCurrency = safeValue<std::string>(j, "tax_currency");
        dto.publicAmount = safeValue<std::string>(j, "public_amount");
        dto.publicCurrency = safeValue<std::string>(j, "public_currency");
        dto.dueAtAccommodationAmount = safeValue<std::string>(j, "due_at_accommodation_amount");
        dto.dueAtAccommodationCurrency = safeValue<std::string>(j, "due_at_accommodation_currency");
        dto.feeAmount = safeValue<std::string>(j, "fee_amount");
        dto.feeCurrency = safeValue<std::string>(j, "fee_currency");
        dto.estimatedCommissionAmount = safeValue<std::string>(j, "estimated_commission_amount");
        dto.estimatedCommissionCurrency = safeValue<std::string>(j, "estimated_commission_currency");
        dto.paymentType = safeValue<std::string>(j, "payment_type");
        dto.boardType = safeValue<std::string>(j, "board_type");
        dto.code = safeValue<std::string>(j, "code");
        dto.quantityAvailable = safeValue<int>(j, "quantity_available", 0);
        dto.expiresAt = safeValue<std::string>(j, "expires_at");
        dto.loyaltyProgrammeRequired = safeValue<bool>(j, "loyalty_programme_required", false);
        dto.negotiatedRateId = safeValue<std::string>(j, "negotiated_rate_id");

        if (j.contains("deal_types") && j["deal_types"].is_array())
        {
            for (const auto &dt : j["deal_types"])
                dto.dealTypes.push_back(dt.get<std::string>());
        }

        if (j.contains("cancellation_timeline") && j["cancellation_timeline"].is_array())
        {
            for (const auto &ct : j["cancellation_timeline"])
                dto.cancellationTimeline.push_back(parseCancellationTimeline(ct));
        }

        if (j.contains("conditions") && j["conditions"].is_array())
        {
            for (const auto &c : j["conditions"])
                dto.conditions.push_back(parseCondition(c));
        }

        return dto;
    }

    static DuffelHotelBedDTO parseBed(const json &j)
    {
        DuffelHotelBedDTO dto;
        dto.type = safeValue<std::string>(j, "type");
        dto.count = safeValue<int>(j, "count", 0);
        return dto;
    }

    static DuffelHotelRoomDTO parseRoom(const json &j)
    {
        DuffelHotelRoomDTO dto;
        dto.name = safeValue<std::string>(j, "name");

        if (j.contains("beds") && j["beds"].is_array())
        {
            for (const auto &b : j["beds"])
                dto.beds.push_back(parseBed(b));
        }

        if (j.contains("rates") && j["rates"].is_array())
        {
            for (const auto &r : j["rates"])
                dto.rates.push_back(parseRate(r));
        }

        return dto;
    }

    static DuffelHotelAmenityDTO parseAmenity(const json &j)
    {
        DuffelHotelAmenityDTO dto;
        dto.type = safeValue<std::string>(j, "type");
        dto.description = safeValue<std::string>(j, "description");
        return dto;
    }

    static DuffelHotelAccommodationDTO parseAccommodation(const json &j)
    {
        DuffelHotelAccommodationDTO dto;
        dto.id = safeValue<std::string>(j, "id");
        dto.name = safeValue<std::string>(j, "name");
        dto.description = safeValue<std::string>(j, "description");
        dto.rating = safeValue<double>(j, "rating", 0.0);
        dto.reviewScore = safeValue<double>(j, "review_score", 0.0);
        dto.reviewCount = safeValue<int>(j, "review_count", 0);
        dto.phoneNumber = safeValue<std::string>(j, "phone_number");
        dto.email = safeValue<std::string>(j, "email");
        dto.supportedLoyaltyProgramme = safeValue<std::string>(j, "supported_loyalty_programme");

        if (j.contains("location"))
        {
            const auto &loc = j["location"];

            if (loc.contains("geographic_coordinates"))
            {
                const auto &geo = loc["geographic_coordinates"];

                dto.location.longitude = safeValue<double>(geo, "longitude", 0.0);
                dto.location.latitude = safeValue<double>(geo, "latitude", 0.0);
            }
            if (loc.contains("address"))
            {
                const auto &addr = loc["address"];
                dto.location.address.cityName = safeValue<std::string>(addr, "city_name");
                dto.location.address.countryCode = safeValue<std::string>(addr, "country_code");
                dto.location.address.lineOne = safeValue<std::string>(addr, "line_one");
                dto.location.address.postalCode = safeValue<std::string>(addr, "postal_code");
                dto.location.address.region = safeValue<std::string>(addr, "region");
            }
        }

        if (j.contains("check_in_information"))
        {
            const auto &ci = j["check_in_information"];
            dto.checkInInformation.checkInAfterTime = safeValue<std::string>(ci, "check_in_after_time");
            dto.checkInInformation.checkInBeforeTime = safeValue<std::string>(ci, "check_in_before_time");
            dto.checkInInformation.checkOutBeforeTime = safeValue<std::string>(ci, "check_out_before_time");
        }

        if (j.contains("key_collection"))
        {
            dto.keyCollection.instructions = safeValue<std::string>(j["key_collection"], "instructions");
        }

        if (j.contains("chain"))
        {
            dto.chain.id = safeValue<std::string>(j["chain"], "id");
            dto.chain.name = safeValue<std::string>(j["chain"], "name");
        }

        if (j.contains("brand"))
        {
            dto.brand.id = safeValue<std::string>(j["brand"], "id");
            dto.brand.name = safeValue<std::string>(j["brand"], "name");
        }

        if (j.contains("amenities") && j["amenities"].is_array())
        {
            for (const auto &a : j["amenities"])
                dto.amenities.push_back(parseAmenity(a));
        }

        if (j.contains("rooms") && j["rooms"].is_array())
        {
            for (const auto &r : j["rooms"])
                dto.rooms.push_back(parseRoom(r));
        }

        return dto;
    }

    static DuffelHotelGuestDTO parseGuest(const json &j)
    {
        DuffelHotelGuestDTO dto;
        dto.type = safeValue<std::string>(j, "type");
        dto.age = safeValue<int>(j, "age", 0);
        return dto;
    }

    Result<DuffelHotelSearchResponseDTO> DuffelHotelParser::parse(const std::string &raw)
    {
        try
        {
            json root = json::parse(raw);

            if (!root.contains("data") || !root["data"].contains("results"))
                return Result<DuffelHotelSearchResponseDTO>::failure("Invalid Duffel hotel response");

            DuffelHotelSearchResponseDTO response;
            response.createdAt = safeValue<std::string>(root["data"], "created_at");

            for (const auto &resultJson : root["data"]["results"])
            {
                DuffelHotelResultDTO result;

                result.id = safeValue<std::string>(resultJson, "id");
                result.checkInDate = safeValue<std::string>(resultJson, "check_in_date");
                result.checkOutDate = safeValue<std::string>(resultJson, "check_out_date");
                result.rooms = safeValue<int>(resultJson, "rooms", 1);
                result.expiresAt = safeValue<std::string>(resultJson, "expires_at");

                result.cheapestRateTotalAmount = safeValue<std::string>(resultJson, "cheapest_rate_total_amount");
                result.cheapestRateCurrency = safeValue<std::string>(resultJson, "cheapest_rate_currency");
                result.cheapestRatePublicAmount = safeValue<std::string>(resultJson, "cheapest_rate_public_amount");
                result.cheapestRatePublicCurrency = safeValue<std::string>(resultJson, "cheapest_rate_public_currency");
                result.cheapestRateDueAtAccommodationAmount = safeValue<std::string>(resultJson, "cheapest_rate_due_at_accommodation_amount");
                result.cheapestRateDueAtAccommodationCurrency = safeValue<std::string>(resultJson, "cheapest_rate_due_at_accommodation_currency");
                result.cheapestRateBaseAmount = safeValue<std::string>(resultJson, "cheapest_rate_base_amount");
                result.cheapestRateBaseCurrency = safeValue<std::string>(resultJson, "cheapest_rate_base_currency");

                if (resultJson.contains("accommodation"))
                    result.accommodation = parseAccommodation(resultJson["accommodation"]);

                if (resultJson.contains("guests") && resultJson["guests"].is_array())
                {
                    for (const auto &g : resultJson["guests"])
                        result.guests.push_back(parseGuest(g));
                }

                if (resultJson.contains("supported_negotiated_rates") && resultJson["supported_negotiated_rates"].is_array())
                {
                    for (const auto &nr : resultJson["supported_negotiated_rates"])
                    {
                        DuffelHotelSupportedNegotiatedRateDTO dto;
                        dto.id = safeValue<std::string>(nr, "id");
                        dto.displayName = safeValue<std::string>(nr, "display_name");
                        result.supportedNegotiatedRates.push_back(std::move(dto));
                    }
                }

                response.results.push_back(std::move(result));
            }

            return Result<DuffelHotelSearchResponseDTO>::success(std::move(response));
        }
        catch (const std::exception &e)
        {
            return Result<DuffelHotelSearchResponseDTO>::failure(e.what());
        }
    }

} // namespace duffel
