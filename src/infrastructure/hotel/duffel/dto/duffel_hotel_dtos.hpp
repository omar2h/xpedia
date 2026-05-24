#pragma once

#include <string>
#include <vector>

namespace duffel
{

struct DuffelHotelCancellationTimelineDTO
{
    std::string before;
    std::string refundAmount;
    std::string currency;
};

struct DuffelHotelConditionDTO
{
    std::string title;
    std::string description;
};

struct DuffelHotelRateDTO
{
    std::string id;
    std::string name;
    std::string description;
    std::string totalAmount;
    std::string totalCurrency;
    std::string baseAmount;
    std::string baseCurrency;
    std::string taxAmount;
    std::string taxCurrency;
    std::string publicAmount;
    std::string publicCurrency;
    std::string dueAtAccommodationAmount;
    std::string dueAtAccommodationCurrency;
    std::string feeAmount;
    std::string feeCurrency;
    std::string estimatedCommissionAmount;
    std::string estimatedCommissionCurrency;
    std::string paymentType;
    std::string boardType;
    std::string code;
    int quantityAvailable{};
    std::string expiresAt;
    bool loyaltyProgrammeRequired{};
    std::string negotiatedRateId;
    std::vector<std::string> dealTypes;
    std::vector<DuffelHotelCancellationTimelineDTO> cancellationTimeline;
    std::vector<DuffelHotelConditionDTO> conditions;
};

struct DuffelHotelBedDTO
{
    std::string type;
    int count{};
};

struct DuffelHotelRoomDTO
{
    std::string name;
    std::vector<DuffelHotelBedDTO> beds;
    std::vector<DuffelHotelRateDTO> rates;
};

struct DuffelHotelAmenityDTO
{
    std::string type;
    std::string description;
};

struct DuffelHotelChainDTO
{
    std::string id;
    std::string name;
};

struct DuffelHotelBrandDTO
{
    std::string id;
    std::string name;
};

struct DuffelHotelCheckInInfoDTO
{
    std::string checkInAfterTime;
    std::string checkInBeforeTime;
    std::string checkOutBeforeTime;
};

struct DuffelHotelKeyCollectionDTO
{
    std::string instructions;
};

struct DuffelHotelAddressDTO
{
    std::string cityName;
    std::string countryCode;
    std::string lineOne;
    std::string postalCode;
    std::string region;
};

struct DuffelHotelLocationDTO
{
    double latitude{};
    double longitude{};
    DuffelHotelAddressDTO address;
};

struct DuffelHotelAccommodationDTO
{
    std::string id;
    std::string name;
    std::string description;
    double rating{};
    double reviewScore{};
    int reviewCount{};
    std::string phoneNumber;
    std::string email;
    std::string supportedLoyaltyProgramme;
    DuffelHotelLocationDTO location;
    DuffelHotelCheckInInfoDTO checkInInformation;
    DuffelHotelKeyCollectionDTO keyCollection;
    DuffelHotelChainDTO chain;
    DuffelHotelBrandDTO brand;
    std::vector<DuffelHotelAmenityDTO> amenities;
    std::vector<DuffelHotelRoomDTO> rooms;
};

struct DuffelHotelSupportedNegotiatedRateDTO
{
    std::string id;
    std::string displayName;
};

struct DuffelHotelGuestDTO
{
    std::string type;
    int age{};
};

struct DuffelHotelResultDTO
{
    std::string id;
    std::string checkInDate;
    std::string checkOutDate;
    int rooms{};
    std::string expiresAt;
    std::string cheapestRateTotalAmount;
    std::string cheapestRateCurrency;
    std::string cheapestRatePublicAmount;
    std::string cheapestRatePublicCurrency;
    std::string cheapestRateDueAtAccommodationAmount;
    std::string cheapestRateDueAtAccommodationCurrency;
    std::string cheapestRateBaseAmount;
    std::string cheapestRateBaseCurrency;
    DuffelHotelAccommodationDTO accommodation;
    std::vector<DuffelHotelGuestDTO> guests;
    std::vector<DuffelHotelSupportedNegotiatedRateDTO> supportedNegotiatedRates;
};

struct DuffelHotelSearchResponseDTO
{
    std::vector<DuffelHotelResultDTO> results;
    std::string createdAt;
    std::string errorMessage;
};

} // namespace duffel
