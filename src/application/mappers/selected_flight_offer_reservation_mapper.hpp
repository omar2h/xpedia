#pragma once

#include "../../domain/entities/flight.hpp"
#include "../../domain/entities/flight_reservation.hpp"
#include "../../domain/entities/reservation.hpp"
#include "../../domain/entities/reservation_category.hpp"
#include "../../domain/factories/reservation_factory.hpp"
#include "../../domain/request_type.hpp"
#include "../dto/selected_flight_offer.hpp"

#include <memory>
#include <stdexcept>

class SelectedFlightOfferReservationMapper
{
  public:
    static std::unique_ptr<Reservation> map(ReservationFactory& reservationFactory,
                                            const SelectedFlightOffer& selectedOffer)
    {
        const auto& offer = selectedOffer.offer;
        const auto& input = selectedOffer.input;

        double totalAmount = 0.0;
        try
        {
            totalAmount = std::stod(offer.totalAmount);
        }
        catch (const std::exception&)
        {
            return nullptr;
        }

        auto flight = std::make_unique<Flight>();
        if (!offer.segments.empty())
        {
            const auto& first = offer.segments.front();
            const auto& last = offer.segments.back();

            flight->setAirline(first.airline.name);
            flight->setFlightNumber(first.flightNumber);
            flight->setFrom(first.fromIata);
            flight->setTo(last.toIata);
            flight->setDate(first.departureTime.substr(0, 10));
        }

        flight->setTotalCost(totalAmount);
        flight->setProviderId(offer.providerId);
        flight->setRequestType(RequestType::flight);
        flight->setCategory(ReservationCategory::flight);

        auto reservation = reservationFactory.getReservation(RequestType::flight);
        if (!reservation)
        {
            return nullptr;
        }

        reservation->setItem(*flight);

        auto* flightReservation = dynamic_cast<FlightReservation*>(reservation.get());
        if (flightReservation)
        {
            if (!offer.segments.empty())
            {
                flightReservation->setFrom(offer.segments.front().fromIata);
                flightReservation->setTo(offer.segments.back().toIata);
            }

            flightReservation->setAdults(input.adults);
            flightReservation->setCost(totalAmount);
        }

        return reservation;
    }
};
