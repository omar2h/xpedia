#pragma once

#include "../dto/selected_hotel_offer.hpp"

class Itinerary;
class ReservationFactory;

class AddHotelToItineraryUseCase
{
    ReservationFactory& m_reservationFactory;

  public:
    explicit AddHotelToItineraryUseCase(ReservationFactory& reservationFactory);

    bool execute(Itinerary& itinerary, const SelectedHotelOffer& selectedOffer);
};
