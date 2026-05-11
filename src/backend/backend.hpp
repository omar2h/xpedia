#pragma once

#include "../model/user.hpp"
#include "managers/flights_manager.hpp"
#include "../model/itinerary.hpp"
#include "../model/customer.hpp"
#include "payments/payment_strategy.hpp"
#include "../frontend/frontend_interface.hpp"

class Database;

class Backend
{
    Database &m_database;

public:
    explicit Backend(Database &database);

    void save_user_in_db(User &);
    User user_login(const std::string &, const std::string &);
    void create_itinerary(User &, IFrontend &);
    void add_new_item(RequestType, Itinerary &, IFrontend &);
    std::vector<std::unique_ptr<ItineraryItem>> get_available_reservations(ReservationRequest *, RequestType);
    int make_reservations(Customer &, const Itinerary &, IFrontend &);
    bool confirm_reservations(Customer &customer, const Itinerary &currItinerary);
    bool withdraw_money(const PaymentCard &card, int service, const Itinerary &currItinerary);
    int select_card(Customer &customer, IFrontend &);
    void payItinerary(const Itinerary &, const User &, IFrontend &);
    void add_card(Customer &, IFrontend &);
    void list_itineraries(const User &, IFrontend &);
};
