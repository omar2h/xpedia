#pragma once

#include <string>
#include <vector>

#include "../view_models/view_models.hpp"

class IView
{
public:
    virtual ~IView() = default;

    virtual void showMessage(const std::string&) = 0;
    virtual void showError(const std::string&) = 0;
    virtual void showPrompt(const std::string&) = 0;
    virtual void displayWelcomeMessage(const std::string& firstName, const std::string& lastName) = 0;
    virtual void displayUserProfile(const UserProfileViewModel&) = 0;
    virtual void displayItinerary(const ItineraryViewModel&) = 0;
    virtual void displayItineraries(const std::vector<ItineraryViewModel>&) = 0;
    virtual void showStartMenu() = 0;
    virtual void showMainMenu() = 0;
    virtual void showPaymentOptions(const std::vector<PaymentCardViewModel>&) = 0;
    virtual void showPaymentServices() = 0;
    virtual void showSearchResults(const std::vector<SearchResultViewModel>&) = 0;
    virtual void displayFlightOffers(const FlightOfferListView&) = 0;
    virtual void displayHotelOffers(const HotelOfferListView&) = 0;
};
