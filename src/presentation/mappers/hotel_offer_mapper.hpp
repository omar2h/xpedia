#pragma once

#include "../view_models/view_models.hpp"
#include "domain/value_objects/hotel_offer.hpp"
#include <sstream>
#include <iomanip>

class HotelOfferMapper
{
public:
    static HotelOfferViewModel map(const HotelOffer &offer, const HotelRoomOffer &room, int number)
    {
        HotelOfferViewModel item;

        item.number = number;
        item.title = room.roomName.empty() ? offer.accommodationName
                                           : room.roomName + " | " + room.boardType + " | " + (room.refundable ? "Refundable" : "Non-refundable");
        item.subtitle = offer.accommodationName;
        item.hotelName = offer.accommodationName;

        std::ostringstream oss;

        oss << std::fixed << std::setprecision(2) << room.totalAmount << " " << room.totalCurrency;
        item.priceText = oss.str();
        item.providerText = "Provider: " + offer.providerId;

        return item;
    }
};