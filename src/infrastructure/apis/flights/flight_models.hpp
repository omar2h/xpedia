#pragma once

#include <string>
#include <vector>
#include <optional>

// Flight search parameters
struct FlightSearchParams
{
    std::string from;
    std::string to;
    std::string date;
    int adults = 1;
    int children = 0;
};

// Flight search result
struct FlightResult
{
    double price;
    std::string date;
    std::string airline;
    std::string flightNumber;
    std::string departureTime;
    std::string arrivalTime;
    std::string fromAirport;
    std::string toAirport;
};

// Flight reservation parameters
struct FlightReservationParams
{
    std::string flightId;
    std::string passengerName;
    std::string passengerEmail;
    std::string passengerPhone;
};