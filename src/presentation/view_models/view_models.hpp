#pragma once

#include <string>
#include <vector>

struct FlightOfferViewModel
{
    int number{};

    std::string airline;
    std::string flightNumber;

    std::string route;

    std::string departureTime;
    std::string arrivalTime;

    std::string duration;
    std::string cabin;
    std::string aircraft;

    std::string stops;
    std::string baggage;

    std::string price;

    bool multiSegment{};
};

struct SearchResultViewModel
{
    std::string displayText;
};

struct ItineraryViewModel
{
    std::string summary;
};

struct PaymentCardViewModel
{
    std::string displayText;
};

struct UserProfileViewModel
{
    std::string fullName;
    std::string email;
    std::string phone;
};

struct FlightOfferListView
{
    std::vector<FlightOfferViewModel> offers;
};
