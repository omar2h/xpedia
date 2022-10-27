#ifndef __BACKEND_H__
#define __BACKEND_H__
#include "user.h"
#include "flightsManager.h"
#include "itinerary.h"
#include "customer.h"
#include "paymentStrategy.h"
class BackEnd
{

public:
    static void save_user_in_db(User &);
    static User user_login(const std::string &, const std::string &);
    static void create_itinerary(User &);
    static void add_flight(RequestType, Itinerary &);
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
#endif // __BACKEND_H__