#include "add_hotel_to_itinerary_use_case.hpp"

#include "../../domain/entities/itinerary.hpp"
#include "../../domain/factories/reservation_factory.hpp"
#include "../mappers/selected_hotel_offer_reservation_mapper.hpp"

#include <utility>

AddHotelToItineraryUseCase::AddHotelToItineraryUseCase(ReservationFactory& reservationFactory)
    : m_reservationFactory(reservationFactory)
{
}

bool AddHotelToItineraryUseCase::execute(Itinerary& itinerary, const SelectedHotelOffer& selectedOffer)
{
    auto reservation = SelectedHotelOfferReservationMapper::map(m_reservationFactory, selectedOffer);
    if (!reservation)
        return false;

    itinerary.addItem(std::move(reservation));
    return true;
}
