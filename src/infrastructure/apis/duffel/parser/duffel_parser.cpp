#include "duffel_parser.hpp"
#include "../dto/duffel_dtos.hpp"
#include "json.hpp"
#include <vector>

using json = nlohmann::json;

namespace duffel
{

    static std::string getString(
        const json &j,
        const std::string &key,
        const std::string &fallback = "")
    {
        if (!j.contains(key) || j[key].is_null())
            return fallback;

        if (!j[key].is_string())
            return fallback;

        return j[key].get<std::string>();
    }

    static int getInt(
        const json &j,
        const std::string &key,
        int fallback = 0)
    {
        if (!j.contains(key) || j[key].is_null())
            return fallback;

        if (!j[key].is_number_integer())
            return fallback;

        return j[key].get<int>();
    }

    static DuffelSegmentDTO parseSegment(const json &segJson)
    {
        DuffelSegmentDTO seg;

        seg.id = getString(segJson, "id");

        if (segJson.contains("origin") &&
            segJson["origin"].is_object())
        {
            seg.originIata =
                getString(segJson["origin"], "iata_code");
        }

        if (segJson.contains("destination") &&
            segJson["destination"].is_object())
        {
            seg.destinationIata =
                getString(segJson["destination"], "iata_code");
        }

        seg.departingAt = getString(segJson, "departing_at");
        seg.arrivingAt = getString(segJson, "arriving_at");

        if (segJson.contains("operating_carrier") &&
            segJson["operating_carrier"].is_object())
        {
            seg.airlineName =
                getString(segJson["operating_carrier"], "name");
        }
        else if (segJson.contains("marketing_carrier") &&
                 segJson["marketing_carrier"].is_object())
        {
            seg.airlineName =
                getString(segJson["marketing_carrier"], "name");
        }

        seg.flightNumber = getString(segJson, "flight_number");

        if (segJson.contains("aircraft") &&
            segJson["aircraft"].is_object())
        {
            seg.aircraftName =
                getString(segJson["aircraft"], "name");
        }

        seg.cabinClass =
            getString(segJson, "cabin_class", "economy");

        if (segJson.contains("passengers") &&
            segJson["passengers"].is_array())
        {
            for (const auto &pax : segJson["passengers"])
            {
                DuffelPassengerDTO passenger;

                passenger.cabinClass =
                    getString(pax, "cabin_class", "economy");

                if (pax.contains("baggages") &&
                    pax["baggages"].is_array())
                {
                    for (const auto &bag : pax["baggages"])
                    {
                        DuffelBaggageDTO baggage;

                        baggage.type =
                            getString(bag, "type");

                        baggage.quantity =
                            getInt(bag, "quantity", 0);

                        passenger.baggages.push_back(
                            std::move(baggage));
                    }
                }

                seg.passengers.push_back(std::move(passenger));
            }
        }

        return seg;
    }

    static DuffelSliceDTO parseSlice(const json &sliceJson)
    {
        DuffelSliceDTO slice;

        if (sliceJson.contains("origin") &&
            sliceJson["origin"].is_object())
        {
            slice.originIata =
                getString(sliceJson["origin"], "iata_code");
        }

        if (sliceJson.contains("destination") &&
            sliceJson["destination"].is_object())
        {
            slice.destinationIata =
                getString(sliceJson["destination"], "iata_code");
        }

        slice.departureAt =
            getString(sliceJson, "departure_at");

        slice.arrivalAt =
            getString(sliceJson, "arrival_at");

        if (sliceJson.contains("segments") &&
            sliceJson["segments"].is_array())
        {
            for (const auto &segJson : sliceJson["segments"])
            {
                slice.segments.push_back(
                    parseSegment(segJson));
            }
        }

        return slice;
    }

    static DuffelOfferDTO parseOffer(const json &offerJson)
    {
        DuffelOfferDTO offer;

        offer.id =
            getString(offerJson, "id");

        offer.totalAmount =
            getString(offerJson, "total_amount", "0");

        offer.totalCurrency =
            getString(offerJson, "total_currency", "USD");

        offer.duration =
            getString(offerJson, "duration");

        if (offerJson.contains("owner") &&
            offerJson["owner"].is_object())
        {
            offer.airlineName =
                getString(offerJson["owner"], "name", "Unknown");

            offer.airlineIata =
                getString(offerJson["owner"], "iata_code");
        }

        offer.expiresAt =
            getString(offerJson, "expires_at");

        if (offerJson.contains("slices") &&
            offerJson["slices"].is_array())
        {
            for (const auto &sliceJson : offerJson["slices"])
            {
                offer.slices.push_back(
                    parseSlice(sliceJson));
            }
        }

        return offer;
    }

    DuffelResponseDTO DuffelParser::parse(
        const std::string &rawJson)
    {
        DuffelResponseDTO response;

        try
        {
            auto j = json::parse(rawJson);

            if (j.contains("errors") &&
                j["errors"].is_array())
            {
                auto &errArr = j["errors"];

                if (!errArr.empty() &&
                    errArr[0].is_object())
                {
                    response.errorMessage =
                        getString(errArr[0], "title", "API error");
                }
                else
                {
                    response.errorMessage =
                        "Unknown API error";
                }

                return response;
            }

            if (j.contains("error") &&
                j["error"].is_object())
            {
                response.errorMessage =
                    getString(j["error"], "message", "Unknown error");

                return response;
            }

            if (!j.contains("data") ||
                !j["data"].is_object())
            {
                response.errorMessage =
                    "API response missing 'data' field";

                return response;
            }

            auto &data = j["data"];

            if (!data.contains("offers") ||
                !data["offers"].is_array())
            {
                response.errorMessage =
                    "API response missing 'offers' in data";

                return response;
            }

            for (const auto &offerJson : data["offers"])
            {
                response.offers.push_back(
                    parseOffer(offerJson));
            }
        }
        catch (const std::exception &e)
        {
            response.errorMessage = e.what();
        }

        return response;
    }

} // namespace duffel