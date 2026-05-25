#include "add_hotel_to_itinerary_use_case.hpp"

#include "../../domain/entities/hotel_reservation.hpp"
#include "../../domain/entities/hotel_room.hpp"
#include "../../domain/entities/itinerary.hpp"
#include "../../domain/entities/reservation_category.hpp"
#include "../../domain/factories/reservation_factory.hpp"
#include "../../domain/request_type.hpp"

#include <memory>

AddHotelToItineraryUseCase::AddHotelToItineraryUseCase(ReservationFactory &reservationFactory)
    : m_reservationFactory(reservationFactory) {}

bool AddHotelToItineraryUseCase::execute(Itinerary &itinerary, const SelectedHotelOffer &selectedOffer)
{
    const auto &offer = selectedOffer.offer;
    const auto &input = selectedOffer.input;

    auto room = std::make_unique<HotelRoom>();
    room->setHotelName(offer.accommodationName);
    room->setDateFrom(offer.checkInDate);
    room->setDateTo(offer.checkOutDate);
    room->setProviderId(offer.providerId);
    room->setRequestType(RequestType::hotel);
    room->setCategory(ReservationCategory::hotel);

    double price = offer.totalPrice;
    if (!offer.roomOffers.empty())
    {
        room->setRoomType(offer.roomOffers[0].roomName);
        room->setAvailableRooms(offer.roomOffers[0].quantityAvailable);
        room->setPricePerNight(offer.roomOffers[0].totalAmount);
        price = offer.roomOffers[0].totalAmount;
    }

    auto reservation = m_reservationFactory.getReservation(RequestType::hotel);
    if (!reservation)
        return false;
    reservation->setItem(*room);

    auto *hotelRes = dynamic_cast<HotelReservation *>(reservation.get());
    if (hotelRes)
    {
        hotelRes->setCity(offer.cityName);
        hotelRes->setRooms(input.rooms > 0 ? input.rooms : 1);
        hotelRes->setAdults(input.adults);
        hotelRes->setCost(price);
    }

    itinerary.addItem(std::move(reservation));
    return true;
}
