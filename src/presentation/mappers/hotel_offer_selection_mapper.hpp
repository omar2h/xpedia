#pragma once

#include "hotel_offer_mapper.hpp"

#include <algorithm>
#include <utility>
#include <vector>

struct HotelOfferSelectionList
{
    HotelOfferListView viewModel;
    std::vector<std::pair<int, int>> selectionMap;
};

class HotelOfferSelectionMapper
{
  public:
    static HotelOfferSelectionList map(const std::vector<HotelOffer>& offers)
    {
        HotelOfferSelectionList result;

        int index = 1;
        int hotelCount = 0;

        for (int oi = 0; oi < static_cast<int>(offers.size()) && hotelCount < 5; oi++)
        {
            const auto& offer = offers[oi];
            hotelCount++;
            bool firstRoom = true;

            if (offer.roomOffers.empty())
            {
                HotelRoomOffer room;
                room.totalAmount = offer.totalPrice;
                room.totalCurrency = offer.currency;

                auto item = HotelOfferMapper::map(offer, room, index++);
                item.hotelName = offer.accommodationName;

                result.viewModel.offers.push_back(std::move(item));
                result.selectionMap.push_back({oi, -1});
                continue;
            }

            int maxRooms = std::min(static_cast<int>(offer.roomOffers.size()), 5);
            for (int ri = 0; ri < maxRooms; ri++)
            {
                auto item = HotelOfferMapper::map(offer, offer.roomOffers[ri], index++);

                if (firstRoom)
                {
                    item.hotelName = offer.accommodationName;
                    firstRoom = false;
                }

                result.viewModel.offers.push_back(std::move(item));
                result.selectionMap.push_back({oi, ri});
            }
        }

        return result;
    }
};
