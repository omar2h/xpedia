#include "add_flight_to_itinerary_use_case.hpp"

#include "../../domain/entities/itinerary.hpp"
#include "../../domain/factories/reservation_factory.hpp"
#include "../mappers/selected_flight_offer_reservation_mapper.hpp"

#include <utility>

AddFlightToItineraryUseCase::AddFlightToItineraryUseCase(ReservationFactory &reservationFactory)
    : m_reservationFactory(reservationFactory) {}

bool AddFlightToItineraryUseCase::execute(Itinerary &itinerary, const SelectedFlightOffer &selectedOffer)
{
    auto reservation = SelectedFlightOfferReservationMapper::map(m_reservationFactory, selectedOffer);
    if (!reservation)
        return false;

    itinerary.addItem(std::move(reservation));
    return true;
}
