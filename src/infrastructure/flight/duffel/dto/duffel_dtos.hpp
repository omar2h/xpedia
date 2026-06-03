#pragma once

#include <string>
#include <vector>

namespace duffel
{

struct DuffelBaggageDTO
{
    std::string type;
    int quantity{};
};

struct DuffelPassengerDTO
{
    std::string cabinClass;
    std::vector<DuffelBaggageDTO> baggages;
};

struct DuffelSegmentDTO
{
    std::string id;
    std::string originIata;
    std::string destinationIata;
    std::string departingAt;
    std::string arrivingAt;
    std::string airlineName;
    std::string airlineIata;
    std::string flightNumber;
    std::string aircraftName;
    std::string cabinClass;
    std::vector<DuffelPassengerDTO> passengers;
};

struct DuffelSliceDTO
{
    std::string originIata;
    std::string destinationIata;
    std::string departureAt;
    std::string arrivalAt;
    std::vector<DuffelSegmentDTO> segments;
};

struct DuffelOfferDTO
{
    std::string id;
    std::string airlineName;
    std::string airlineIata;
    std::string totalAmount;
    std::string totalCurrency;
    std::string duration;
    std::string expiresAt;
    std::vector<DuffelSliceDTO> slices;
};

struct DuffelResponseDTO
{
    std::vector<DuffelOfferDTO> offers;
    std::string errorMessage;
};

} // namespace duffel