#pragma once

#include <string>
#include <vector>

struct FlightOffer;

namespace duffel
{

struct DuffelResponseDTO;

class DuffelMapper
{
public:
    std::vector<FlightOffer> toFlightOffers(const DuffelResponseDTO &response);

private:
    static int extractCheckedBags(const DuffelResponseDTO &response, std::size_t offerIdx, std::size_t segmentIdx);
    static std::string formatDuration(const std::string &iso8601);
};

} // namespace duffel
