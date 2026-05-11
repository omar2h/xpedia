#pragma once

#include "../application/frontend_interface.hpp"

class FlightRequest;
class HotelRequest;
class LoginHandler;
class SignupHandler;
class IOutput;
class IInput;

class ConsoleFrontend : public IFrontend
{
    LoginHandler &m_loginHandler;
    SignupHandler &m_signupHandler;
    IOutput &m_output;
    IInput &m_input;

public:
    ConsoleFrontend(LoginHandler &loginHandler,
                    SignupHandler &signupHandler, IOutput &output, IInput &input);

    [[nodiscard]] int displayCreateItineraryMenu() override;
    void readRequestData(ReservationRequest &, RequestType) override;
    [[nodiscard]] int readReservationChoice(const std::vector<std::unique_ptr<ItineraryItem>> &) override;
    [[nodiscard]] int displayPaymentOptions(const std::vector<PaymentCard> &) override;
    [[nodiscard]] PaymentCard readCard() override;
    [[nodiscard]] int displayPaymentServices() override;
    void displayItinerary(const Itinerary &) override;
    void displayItineraries(const std::vector<Itinerary> &) override;
    [[nodiscard]] int showStartMenu() override;
    void displayWelcomeMessage(const std::string &, const std::string &) override;
    [[nodiscard]] int displayMainMenu() override;
    void displayUserProfile(const User &user) override;
    [[nodiscard]] User login() override;
    void signup() override;
    void showMessage(const std::string &msg) override;
    void showError(const std::string &msg) override;

private:
    void readFlightRequestData(FlightRequest &);
    void readHotelRequestData(HotelRequest &);
};