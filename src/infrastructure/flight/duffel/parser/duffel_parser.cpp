#include "duffel_parser.hpp"

#include "../dto/duffel_dtos.hpp"
#include "../utils/json_utils.hpp"

using json = nlohmann::json;
using json_utils::safeValue;

namespace duffel
{
    Result<duffel::DuffelResponseDTO> DuffelParser::parse(const std::string &raw)
    {
        try
        {
            json root = json::parse(raw);

            if (!root.contains("data") || !root["data"].contains("offers"))
                return Result<duffel::DuffelResponseDTO>::failure("Invalid Duffel response");

            duffel::DuffelResponseDTO response;

            for (const auto &offerJson : root["data"]["offers"])
            {
                duffel::DuffelOfferDTO offer;

                offer.id = safeValue<std::string>(offerJson, "id");
                offer.totalAmount = safeValue<std::string>(offerJson, "total_amount");
                offer.totalCurrency = safeValue<std::string>(offerJson, "total_currency");
                offer.duration = safeValue<std::string>(offerJson, "total_duration");
                offer.expiresAt = safeValue<std::string>(offerJson, "expires_at");

                offer.airlineName =
                    offerJson.contains("owner") && !offerJson["owner"].is_null()
                        ? safeValue<std::string>(offerJson["owner"], "name")
                        : "";

                offer.airlineIata =
                    offerJson.contains("owner") && !offerJson["owner"].is_null()
                        ? safeValue<std::string>(offerJson["owner"], "iata_code")
                        : "";

                if (offerJson.contains("slices") && offerJson["slices"].is_array())
                {
                    for (const auto &sliceJson : offerJson["slices"])
                    {
                        duffel::DuffelSliceDTO slice;

                        slice.originIata =
                            sliceJson.contains("origin") && !sliceJson["origin"].is_null()
                                ? safeValue<std::string>(sliceJson["origin"], "iata_code")
                                : "";

                        slice.destinationIata =
                            sliceJson.contains("destination") && !sliceJson["destination"].is_null()
                                ? safeValue<std::string>(sliceJson["destination"], "iata_code")
                                : "";

                        slice.departureAt = safeValue<std::string>(sliceJson, "departing_at");
                        slice.arrivalAt = safeValue<std::string>(sliceJson, "arriving_at");

                        if (sliceJson.contains("segments") && sliceJson["segments"].is_array())
                        {
                            for (const auto &segmentJson : sliceJson["segments"])
                            {
                                duffel::DuffelSegmentDTO segment;

                                segment.flightNumber = safeValue<std::string>(segmentJson, "flight_number");
                                segment.departingAt = safeValue<std::string>(segmentJson, "departing_at");
                                segment.arrivingAt = safeValue<std::string>(segmentJson, "arriving_at");
                                segment.cabinClass = safeValue<std::string>(segmentJson, "cabin_class");

                                segment.originIata =
                                    segmentJson.contains("origin") && !segmentJson["origin"].is_null()
                                        ? safeValue<std::string>(segmentJson["origin"], "iata_code")
                                        : "";

                                segment.destinationIata =
                                    segmentJson.contains("destination") && !segmentJson["destination"].is_null()
                                        ? safeValue<std::string>(segmentJson["destination"], "iata_code")
                                        : "";

                                segment.airlineName =
                                    segmentJson.contains("operating_carrier") && !segmentJson["operating_carrier"].is_null()
                                        ? safeValue<std::string>(segmentJson["operating_carrier"], "name")
                                        : "";

                                segment.airlineIata =
                                    segmentJson.contains("operating_carrier") && !segmentJson["operating_carrier"].is_null()
                                        ? safeValue<std::string>(segmentJson["operating_carrier"], "iata_code")
                                        : "";

                                segment.aircraftName =
                                    segmentJson.contains("aircraft") && !segmentJson["aircraft"].is_null()
                                        ? safeValue<std::string>(segmentJson["aircraft"], "name")
                                        : "";

                                if (segmentJson.contains("passengers") && segmentJson["passengers"].is_array())
                                {
                                    for (const auto &paxJson : segmentJson["passengers"])
                                    {
                                        duffel::DuffelPassengerDTO passenger;

                                        if (paxJson.contains("baggages") && paxJson["baggages"].is_array())
                                        {
                                            for (const auto &bagJson : paxJson["baggages"])
                                            {
                                                duffel::DuffelBaggageDTO baggage;

                                                baggage.type = safeValue<std::string>(bagJson, "type");
                                                baggage.quantity = safeValue<int>(bagJson, "quantity", 0);

                                                passenger.baggages.push_back(std::move(baggage));
                                            }
                                        }

                                        segment.passengers.push_back(std::move(passenger));
                                    }
                                }

                                slice.segments.push_back(std::move(segment));
                            }
                        }

                        offer.slices.push_back(std::move(slice));
                    }
                }

                response.offers.push_back(std::move(offer));
            }

            return Result<duffel::DuffelResponseDTO>::success(std::move(response));
        }
        catch (const std::exception &e)
        {
            return Result<duffel::DuffelResponseDTO>::failure(e.what());
        }
    }
}