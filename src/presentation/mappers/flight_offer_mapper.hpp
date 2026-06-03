#pragma once

#include "../view_models/view_models.hpp"
#include "domain/value_objects/flight_offer.hpp"

#include <string>

class FlightOfferMapper
{
  public:
    static FlightOfferViewModel map(const FlightOffer& offer, int number)
    {
        FlightOfferViewModel item;

        item.number = number;
        item.price = offer.totalAmount + " " + offer.currency;
        item.duration = offer.duration;
        item.multiSegment = offer.segments.size() > 1;

        if (!offer.segments.empty())
        {
            const auto& first = offer.segments.front();
            const auto& last = offer.segments.back();

            item.airline = first.airline.name;
            item.flightNumber = first.flightNumber;
            item.route = first.fromIata + " -> " + last.toIata;
            item.departureTime = first.departureTime;
            item.arrivalTime = last.arrivalTime;
            item.aircraft = first.aircraft;
            item.cabin = first.cabinClass;
            item.baggage = std::to_string(first.checkedBagQuantity) + " bag(s)";
            item.stops = std::to_string(static_cast<int>(offer.segments.size()) - 1);
        }

        return item;
    }
};
