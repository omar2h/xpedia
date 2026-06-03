#pragma once

#include <string>
#include <vector>

struct HotelOffer;

namespace duffel
{

struct DuffelHotelSearchResponseDTO;

class DuffelHotelMapper
{
  public:
    std::vector<HotelOffer> map(const DuffelHotelSearchResponseDTO& response);
};

} // namespace duffel
