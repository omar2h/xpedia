#pragma once

#include <string>

#include "../dto/duffel_dtos.hpp"

namespace duffel
{

class DuffelParser
{
public:
    DuffelResponseDTO parse(const std::string &rawJson);
};

} // namespace duffel
