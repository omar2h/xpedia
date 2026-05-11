#pragma once

#include "frontend_interface.hpp"

class FlightRequest;
class HotelRequest;
class Application;
class LoginHandler;
class SignupHandler;

class ConsoleFrontend : public IFrontend
{
    Application &m_application;
    LoginHandler &m_loginHandler;
    SignupHandler &m_signupHandler;

public:
    ConsoleFrontend(Application &backend, LoginHandler &loginHandler, SignupHandler &signupHandler);

    int displayCreateItineraryMenu() override;
    void readRequestData(ReservationRequest &, RequestType) override;
    int readReservationChoice(const std::vector<std::unique_ptr<ItineraryItem>> &) override;
    int displayPaymentOptions(const std::vector<PaymentCard> &) override;
    PaymentCard readCard() override;
    int displayPaymentServices() override;
    void displayItinerary(const Itinerary &) override;
    void displayItineraries(const std::vector<Itinerary> &) override;
    int showStartMenu() override;
    void displayWelcomeMessage(const std::string &, const std::string &) override;
    int displayMainMenu() override;
    void displayUserProfile(const User &user) override;
    User login() override;
    void signup() override;
    void showMessage(const std::string &msg) override;
    void showError(const std::string &msg) override;

private:
    void readFlightRequestData(FlightRequest &);
    void readHotelRequestData(HotelRequest &);
};