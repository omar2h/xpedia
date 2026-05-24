#pragma once

#include "../../../../domain/result.hpp"

#include "../dto/duffel_hotel_dtos.hpp"

namespace duffel
{

class DuffelHotelParser
{
public:
    Result<DuffelHotelSearchResponseDTO> parse(const std::string &rawJson);
};

} // namespace duffel
