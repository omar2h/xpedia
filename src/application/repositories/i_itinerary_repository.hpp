#pragma once

#include "../../domain/entities/itinerary.hpp"
#include <vector>
#include <string>

class IItineraryRepository
{
public:
    virtual ~IItineraryRepository() = default;

    virtual void save(
        const std::string &userId,
        const Itinerary &
    ) = 0;

    [[nodiscard]] virtual std::vector<Itinerary>
    findByUserId(const std::string &userId) const = 0;
};
