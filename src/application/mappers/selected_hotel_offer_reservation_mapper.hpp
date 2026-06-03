#pragma once

#include "../../domain/entities/hotel_reservation.hpp"
#include "../../domain/entities/hotel_room.hpp"
#include "../../domain/entities/reservation.hpp"
#include "../../domain/entities/reservation_category.hpp"
#include "../../domain/factories/reservation_factory.hpp"
#include "../../domain/request_type.hpp"
#include "../dto/selected_hotel_offer.hpp"

#include <memory>

class SelectedHotelOfferReservationMapper
{
  public:
    static std::unique_ptr<Reservation> map(ReservationFactory& reservationFactory,
                                            const SelectedHotelOffer& selectedOffer)
    {
        const auto& offer = selectedOffer.offer;
        const auto& input = selectedOffer.input;

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

        auto reservation = reservationFactory.getReservation(RequestType::hotel);
        if (!reservation)
        {
            return nullptr;
        }

        reservation->setItem(*room);

        auto* hotelReservation = dynamic_cast<HotelReservation*>(reservation.get());
        if (hotelReservation)
        {
            hotelReservation->setCity(offer.cityName);
            hotelReservation->setRooms(input.rooms > 0 ? input.rooms : 1);
            hotelReservation->setAdults(input.adults);
            hotelReservation->setCost(price);
        }

        return reservation;
    }
};
