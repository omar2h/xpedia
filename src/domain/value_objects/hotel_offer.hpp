#pragma once

#include <string>
#include <vector>

struct HotelAmenity
{
    std::string type;
    std::string description;
};

struct HotelRoomOffer
{
    std::string roomName;
    std::string rateId;
    std::string rateName;
    std::string totalAmount;
    std::string totalCurrency;
    std::string baseAmount;
    std::string baseCurrency;
    std::string taxAmount;
    std::string taxCurrency;
    std::string boardType;
    int quantityAvailable{};
    std::string expiresAt;
};

struct HotelOffer
{
    std::string providerId;

    std::string searchResultId;
    std::string accommodationId;

    std::string accommodationName;
    std::string description;

    double rating{};
    double reviewScore{};
    int reviewCount{};

    std::string cityName;
    std::string countryCode;
    std::string address;
    std::string phoneNumber;
    std::string email;

    std::string checkInDate;
    std::string checkOutDate;
    int rooms{};

    std::string cheapestRateTotalAmount;
    std::string cheapestRateCurrency;

    std::vector<HotelRoomOffer> roomOffers;
    std::vector<HotelAmenity> amenities;

    std::string expiresAt;
};
