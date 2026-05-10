// #pragma once

// #include "../model/user.hpp"
// #include "../model/requests/flight_request.hpp"
// #include "../model/requests/hotel_request.hpp"
// #include "../model/flight.hpp"
// #include "request_data_reader.hpp"
// #include "../model/payment_card.hpp"
// #include "../model/itinerary.hpp"
// #include "login_handler.hpp"
// #include "signup_handler.hpp"
// #include <string>
// #include <vector>

// class Frontend
// {
//     static RequestDataReader *reader;

// public:
//     static int show_start_menu();
//     static void display_welcome_message(const std::string &, const std::string &);
//     static int display_main_menu();
//     static void display_user_profile(const User &);
//     static int display_create_itinerary_menu();
//     static void read_flight_request_data(FlightRequest &);
//     static void read_hotel_request_data(HotelRequest &);
//     static int read_reservation_choice(const std::vector<ItineraryItem *> &);
//     static void read_request_data(ReservationRequest &, RequestType);
//     static int display_payment_options(const std::vector<PaymentCard> &);
//     static PaymentCard read_card();
//     static int display_payment_services();
//     static void display_itinerary(const Itinerary &);
//     static void display_itineraries(const std::vector<Itinerary> &);
//     static User login();
//     static void signup();
//     virtual ~Frontend()
//     {
//         delete reader;
//         reader = nullptr;
//     }
// };