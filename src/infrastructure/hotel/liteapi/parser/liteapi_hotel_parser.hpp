#pragma once

#include "../../../../domain/result.hpp"

#include "../dto/liteapi_hotel_dtos.hpp"

namespace liteapi
{

class LiteApiHotelParser
{
  public:
    Result<LiteApiHotelResponse> parse(const std::string& rawJson);
};

} // namespace liteapi
