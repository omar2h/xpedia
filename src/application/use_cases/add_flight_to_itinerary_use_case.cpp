#include "add_flight_to_itinerary_use_case.hpp"

#include "../../domain/entities/flight.hpp"
#include "../../domain/entities/flight_reservation.hpp"
#include "../../domain/entities/itinerary.hpp"
#include "../../domain/entities/reservation_category.hpp"
#include "../../domain/factories/reservation_factory.hpp"
#include "../../domain/request_type.hpp"

#include <memory>

AddFlightToItineraryUseCase::AddFlightToItineraryUseCase(ReservationFactory &reservationFactory)
    : m_reservationFactory(reservationFactory) {}

bool AddFlightToItineraryUseCase::execute(Itinerary &itinerary, const SelectedFlightOffer &selectedOffer)
{
    const auto &offer = selectedOffer.offer;
    const auto &input = selectedOffer.input;

    auto flight = std::make_unique<Flight>();
    if (!offer.segments.empty())
    {
        const auto &first = offer.segments.front();
        const auto &last = offer.segments.back();
        flight->setAirline(first.airline.name);
        flight->setFlightNumber(first.flightNumber);
        flight->setFrom(first.fromIata);
        flight->setTo(last.toIata);
        flight->setDate(first.departureTime.substr(0, 10));
    }
    flight->setTotalCost(std::stod(offer.totalAmount));
    flight->setProviderId(offer.providerId);
    flight->setRequestType(RequestType::flight);
    flight->setCategory(ReservationCategory::flight);

    auto reservation = m_reservationFactory.getReservation(RequestType::flight);
    if (!reservation)
        return false;
    reservation->setItem(*flight);

    auto *flightRes = dynamic_cast<FlightReservation *>(reservation.get());
    if (flightRes)
    {
        if (!offer.segments.empty())
        {
            flightRes->setFrom(offer.segments.front().fromIata);
            flightRes->setTo(offer.segments.back().toIata);
        }
        flightRes->setAdults(input.adults);
        flightRes->setCost(std::stod(offer.totalAmount));
    }

    itinerary.addItem(std::move(reservation));
    return true;
}
