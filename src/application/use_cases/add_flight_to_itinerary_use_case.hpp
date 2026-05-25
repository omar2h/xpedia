#pragma once

#include "../dto/selected_flight_offer.hpp"

class Itinerary;
class ReservationFactory;

class AddFlightToItineraryUseCase
{
    ReservationFactory &m_reservationFactory;

public:
    explicit AddFlightToItineraryUseCase(ReservationFactory &reservationFactory);

    bool execute(Itinerary &itinerary, const SelectedFlightOffer &selectedOffer);
};
