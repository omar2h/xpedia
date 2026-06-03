// duffel_parser.hpp

#pragma once

#include "result.hpp"

#include "../dto/duffel_dtos.hpp"

namespace duffel
{

class DuffelParser
{
  public:
    Result<DuffelResponseDTO> parse(const std::string& rawJson);
};

} // namespace duffel