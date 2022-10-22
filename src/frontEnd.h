#ifndef __FRONTEND_H__
#define __FRONTEND_H__
#include "user.h"
#include "flightRequest.h"
#include "flight.h"
#include "requestDataReader.h"
#include <string>
#include <vector>

class FrontEnd
{
    static RequestDataReader *reader;

public:
    static int show_start_menu();
    static void display_welcome_message(const std::string &, const std::string &);
    static int display_main_menu();
    static void display_user_profile(const User &);
    static int display_create_itinerary_menu();
    static void read_flight_request_data(FlightRequest &);
    static int read_flight_choice(const std::vector<Flight> &);
    static void read_request_data(ReservationRequest *, RequestType);

    virtual ~FrontEnd()
    {
        delete reader;
        reader = nullptr;
    }
};
#endif // __FRONTEND_H__