#pragma once

#include "frontend_interface.hpp"

class FlightRequest;
class HotelRequest;
class Application;
class LoginHandler;
class SignupHandler;

class ConsoleFrontend : public IFrontend
{
    Application &m_backend;
    LoginHandler &m_loginHandler;
    SignupHandler &m_signupHandler;

public:
    ConsoleFrontend(Application &backend, LoginHandler &loginHandler, SignupHandler &signupHandler);

    int display_create_itinerary_menu() override;
    void read_request_data(ReservationRequest &, RequestType) override;
    int read_reservation_choice(const std::vector<std::unique_ptr<ItineraryItem>> &) override;
    int display_payment_options(const std::vector<PaymentCard> &) override;
    PaymentCard read_card() override;
    int display_payment_services() override;
    void display_itinerary(const Itinerary &) override;
    void display_itineraries(const std::vector<Itinerary> &) override;
    int show_start_menu() override;
    void display_welcome_message(const std::string &, const std::string &) override;
    int display_main_menu() override;
    void display_user_profile(const User &user) override;
    User login() override;
    void signup() override;
    void show_message(const std::string &msg) override;
    void show_error(const std::string &msg) override;

private:
    void read_flight_request_data(FlightRequest &);
    void read_hotel_request_data(HotelRequest &);
};