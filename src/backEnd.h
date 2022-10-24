#ifndef __BACKEND_H__
#define __BACKEND_H__
#include "user.h"
#include "flightsManager.h"
#include "itinerary.h"
class BackEnd
{

public:
    static void save_user_in_db(User &);
    static User user_login(const std::string &, const std::string &);
    static void create_itinerary(User &);
    static void add_flight(RequestType, Itinerary &);
    static std::vector<ItineraryItem *> get_available_reservations(ReservationRequest *, RequestType);
    static void payItinerary(const Itinerary &, User &);
    // static std::vector<Flight> get_available_flights(const FlightRequest &request);
};
#endif // __BACKEND_H__