#include "duffel_hotel_mapper.hpp"
#include "../../../../domain/value_objects/hotel_offer.hpp"
#include "../dto/duffel_hotel_dtos.hpp"
#include <vector>

namespace duffel
{

std::vector<HotelOffer> DuffelHotelMapper::map(const DuffelHotelSearchResponseDTO& response)
{
    std::vector<HotelOffer> offers;
    offers.reserve(response.results.size());

    for (const auto& src : response.results)
    {
        HotelOffer offer;
        offer.providerId = "duffel";

        offer.searchResultId = src.id;
        offer.accommodationId = src.accommodation.id;
        offer.accommodationName = src.accommodation.name;
        offer.description = src.accommodation.description;
        offer.rating = src.accommodation.rating;
        offer.reviewScore = src.accommodation.reviewScore;
        offer.reviewCount = src.accommodation.reviewCount;
        offer.phoneNumber = src.accommodation.phoneNumber;
        offer.email = src.accommodation.email;
        offer.cityName = src.accommodation.location.address.cityName;
        offer.countryCode = src.accommodation.location.address.countryCode;
        offer.address = src.accommodation.location.address.lineOne;

        offer.checkInDate = src.checkInDate;
        offer.checkOutDate = src.checkOutDate;
        offer.rooms = src.rooms;

        offer.cheapestRateTotalAmount = src.cheapestRateTotalAmount;
        offer.cheapestRateCurrency = src.cheapestRateCurrency;

        offer.expiresAt = src.expiresAt;

        for (const auto& srcAmenity : src.accommodation.amenities)
        {
            HotelAmenity amenity;
            amenity.type = srcAmenity.type;
            amenity.description = srcAmenity.description;
            offer.amenities.push_back(std::move(amenity));
        }

        for (const auto& srcRoom : src.accommodation.rooms)
        {
            for (const auto& srcRate : srcRoom.rates)
            {
                HotelRoomOffer roomOffer;
                roomOffer.roomName = srcRoom.name;
                roomOffer.rateId = srcRate.id;
                roomOffer.rateName = srcRate.name;
                roomOffer.totalAmount = srcRate.totalAmount;
                roomOffer.totalCurrency = srcRate.totalCurrency;
                roomOffer.baseAmount = srcRate.baseAmount;
                roomOffer.baseCurrency = srcRate.baseCurrency;
                roomOffer.taxAmount = srcRate.taxAmount;
                roomOffer.taxCurrency = srcRate.taxCurrency;
                roomOffer.boardType = srcRate.boardType;
                roomOffer.quantityAvailable = srcRate.quantityAvailable;
                roomOffer.expiresAt = srcRate.expiresAt;
                offer.roomOffers.push_back(std::move(roomOffer));
            }
        }

        offers.push_back(std::move(offer));
    }

    return offers;
}

} // namespace duffel
