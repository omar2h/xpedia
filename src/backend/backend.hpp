#pragma once

#include "../model/user.hpp"
#include "managers/flights_manager.hpp"
#include "../model/itinerary.hpp"
#include "../model/customer.hpp"
#include "payments/payment_strategy.hpp"
class Backend
{

public:
    static void save_user_in_db(User &);
    static User user_login(const std::string &, const std::string &);
    static void create_itinerary(User &);
    static void add_new_item(RequestType, Itinerary &);
    static std::vector<ItineraryItem *> get_available_reservations(ReservationRequest *, RequestType);
    static int make_reservations(Customer &customer, const Itinerary &currItinerary);
    static bool confirm_reservations(Customer &customer, const Itinerary &currItinerary);
    static bool withdraw_money(const PaymentCard &card, int service, const Itinerary &currItinerary);
    static int select_card(Customer &customer);
    static void payItinerary(const Itinerary &, const User &);
    static void add_card(Customer &);
    static void list_itineraries(const User &);
    // static std::vector<Flight> get_available_flights(const FlightRequest &request);
};
