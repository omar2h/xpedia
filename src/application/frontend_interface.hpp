#pragma once

#include "../domain/entities/payment_card.hpp"
#include "../domain/entities/itinerary_item.hpp"
#include "requests/reservation_request.hpp"
#include "../domain/entities/user.hpp"
#include <vector>
#include <memory>

class Itinerary;

class IFrontend
{
public:
    virtual ~IFrontend() = default;
    [[nodiscard]] virtual int displayCreateItineraryMenu() = 0;
    virtual void readRequestData(ReservationRequest &, RequestType) = 0;
    [[nodiscard]] virtual int readReservationChoice(const std::vector<std::unique_ptr<ItineraryItem>> &) = 0;
    [[nodiscard]] virtual int displayPaymentOptions(const std::vector<PaymentCard> &) = 0;
    [[nodiscard]] virtual PaymentCard readCard() = 0;
    [[nodiscard]] virtual int displayPaymentServices() = 0;
    virtual void displayItineraries(const std::vector<Itinerary> &) = 0;
    virtual void displayItinerary(const Itinerary &) = 0;
    [[nodiscard]] virtual int showStartMenu() = 0;
    virtual void displayWelcomeMessage(const std::string &, const std::string &) = 0;
    [[nodiscard]] virtual int displayMainMenu() = 0;
    virtual void displayUserProfile(const User &) = 0;
    [[nodiscard]] virtual User login() = 0;
    virtual void signup() = 0;
    virtual void showMessage(const std::string &) = 0;
    virtual void showError(const std::string &) = 0;
};