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
    double totalAmount;
    std::string totalCurrency;
    std::string boardType;
    bool refundable{};
    std::string cancellationDeadline;
    int quantityAvailable{};
};

struct HotelOffer
{
    std::string providerId;

    std::string accommodationId;
    std::string accommodationName;

    std::string cityName;
    std::string countryCode;
    std::string address;

    double rating{};
    double reviewScore{};
    int reviewCount{};

    std::string checkInDate;
    std::string checkOutDate;

    int rooms{};

    double totalPrice = 0.0;
    std::string currency;

    std::string cheapestRateTotalAmount;
    std::string cheapestRateCurrency;

    std::vector<HotelRoomOffer> roomOffers;

    std::vector<HotelAmenity> amenities;
};
