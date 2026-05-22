#pragma once

#include <memory>
#include <vector>
#include <string>

class HotelSearchRequest;
class ItineraryItem;
class Reservation;

class HotelSearchProvider
{
public:
    virtual std::vector<std::unique_ptr<ItineraryItem>> searchHotels(const HotelSearchRequest &request) = 0;

    virtual bool reserve(Reservation *reservation) = 0;

    virtual std::string getName() const = 0;

    virtual ~HotelSearchProvider() = default;
};