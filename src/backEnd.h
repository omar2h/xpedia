#ifndef __BACKEND_H__
#define __BACKEND_H__
#include "user.h"
#include "flightsManager.h"

class BackEnd
{
    static std::vector<FlightsManager *> flightsManagers;

public:
    static void save_user_in_db(User &);
    static User user_login(const std::string &, const std::string &);
    static void create_itinerary(int);
    static void add_flight();
    // static std::vector<Flight> get_available_flights(const FlightRequest &request);
};
#endif // __BACKEND_H__