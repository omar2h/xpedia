#include "duffel_mapper.hpp"
#include "../../../../domain/value_objects/airline.hpp"
#include "../../../../domain/value_objects/flight_offer.hpp"
#include "../../../../domain/value_objects/flight_segment.hpp"
#include "../dto/duffel_dtos.hpp"
#include <regex>
#include <vector>

namespace duffel
{

int DuffelMapper::extractCheckedBags(const DuffelResponseDTO& response, std::size_t offerIdx, std::size_t segmentIdx)
{
    const auto& dto = response.offers[offerIdx];
    if (segmentIdx >= dto.slices.size())
        return 0;

    const auto& slice = dto.slices[segmentIdx];
    if (slice.segments.empty())
        return 0;

    const auto& seg = slice.segments[0];
    for (const auto& pax : seg.passengers)
    {
        for (const auto& bag : pax.baggages)
        {
            if (bag.type == "checked")
                return bag.quantity;
        }
    }
    return 0;
}

std::string DuffelMapper::formatDuration(const std::string& iso8601)
{
    // ISO-8601: PT2H23M → "2h 23m" or PT1H → "1h" or PT45M → "45m"
    if (iso8601.empty())
        return {};

    std::regex pattern(R"(PT(?:(\d+)H)?(?:(\d+)M)?)");
    std::smatch match;
    if (!std::regex_match(iso8601, match, pattern))
        return iso8601;

    std::string result;
    if (match[1].matched)
        result += match[1].str() + "h ";
    if (match[2].matched)
        result += match[2].str() + "m";

    if (result.empty())
        return iso8601;

    // Trim trailing space
    if (!result.empty() && result.back() == ' ')
        result.pop_back();

    return result;
}

std::vector<FlightOffer> DuffelMapper::map(const DuffelResponseDTO& response)
{
    std::vector<FlightOffer> offers;
    offers.reserve(response.offers.size());

    for (std::size_t oi = 0; oi < response.offers.size(); ++oi)
    {
        const auto& src = response.offers[oi];

        FlightOffer offer;
        offer.providerId = "duffel";
        offer.offerId = src.id;
        offer.totalAmount = src.totalAmount;
        offer.currency = src.totalCurrency;
        offer.duration = formatDuration(src.duration);
        offer.expiresAt = src.expiresAt;

        for (std::size_t si = 0; si < src.slices.size(); ++si)
        {
            const auto& sliceDto = src.slices[si];

            if (sliceDto.segments.empty())
            {
                // No segments — create a basic segment from slice info
                FlightSegment seg;
                seg.airline.name = src.airlineName;
                seg.airline.iata = src.airlineIata;
                seg.fromIata = sliceDto.originIata;
                seg.toIata = sliceDto.destinationIata;
                seg.departureTime = sliceDto.departureAt;
                seg.arrivalTime = sliceDto.arrivalAt;
                offer.segments.push_back(std::move(seg));
                continue;
            }

            for (const auto& segDto : sliceDto.segments)
            {
                FlightSegment seg;
                seg.airline.name = segDto.airlineName.empty() ? src.airlineName : segDto.airlineName;
                seg.flightNumber = segDto.flightNumber;
                seg.fromIata = segDto.originIata;
                seg.toIata = segDto.destinationIata;
                seg.departureTime = segDto.departingAt;
                seg.arrivalTime = segDto.arrivingAt;
                seg.aircraft = segDto.aircraftName;
                seg.cabinClass = segDto.cabinClass;
                seg.checkedBagQuantity = extractCheckedBags(response, oi, si);
                offer.segments.push_back(std::move(seg));
            }
        }

        offers.push_back(std::move(offer));
    }

    return offers;
}

} // namespace duffel
