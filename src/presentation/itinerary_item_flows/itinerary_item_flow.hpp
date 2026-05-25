#pragma once

#include <string>

class Itinerary;

class ItineraryItemFlow
{
public:
    virtual ~ItineraryItemFlow() = default;

    virtual std::string label() const = 0;

    virtual bool execute(Itinerary& itinerary) = 0;
};
