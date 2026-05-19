#pragma once

#include "view/view_interface.hpp"

class IOutput;

class ConsoleFrontend : public IView
{
    IOutput& m_output;

public:
    ConsoleFrontend(IOutput& output);

    void showMessage(const std::string&) override;
    void showError(const std::string&) override;
    void showPrompt(const std::string&) override;
    void displayWelcomeMessage(const std::string& firstName, const std::string& lastName) override;
    void displayUserProfile(const UserProfileViewModel&) override;
    void displayItinerary(const ItineraryViewModel&) override;
    void displayItineraries(const std::vector<ItineraryViewModel>&) override;
    void showStartMenu() override;
    void showMainMenu() override;
    void showCreateItineraryMenu() override;
    void showPaymentOptions(const std::vector<PaymentCardViewModel>&) override;
    void showPaymentServices() override;
    void showSearchResults(const std::vector<SearchResultViewModel>&) override;
    void displayFlightOffers(const FlightOfferListView&) override;
};
