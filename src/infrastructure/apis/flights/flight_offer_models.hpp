#pragma once

#include <string>
#include <vector>
#include "flight_search_status.hpp"

using FlightSearchStatus = travel_booking_system::infrastructure::apis::flights::FlightSearchStatus;

enum class CabinClass
{
    Economy,
    PremiumEconomy,
    Business,
    First
};

struct FlightOffer
{
    std::string id;
    std::string airline;
    std::string origin;
    std::string destination;
    std::string departureTime;
    std::string arrivalTime;
    std::string duration;
    bool directFlight = true;
    double price = 0.0;
    std::string currency;
};

struct FlightSearchRequest
{
    std::string origin;
    std::string destination;
    std::string departureDate;
    int adults = 1;
    int children = 0;
    CabinClass cabinClass = CabinClass::Economy;
};

struct FlightSearchResult
{
    std::vector<FlightOffer> offers;
    std::string errorMessage;
    FlightSearchStatus status = FlightSearchStatus::Success;
};