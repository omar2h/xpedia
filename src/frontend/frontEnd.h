#ifndef __FRONTEND_H__
#define __FRONTEND_H__
#include "../model/user.h"
#include "../model/flightRequest.h"
#include "../model/flight.h"
#include "requestDataReader.h"
#include "../model/paymentCard.h"
#include "../model/itinerary.h"
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
    static int read_reservation_choice(const std::vector<ItineraryItem *> &);
    static void read_request_data(ReservationRequest *&, RequestType);
    static int display_payment_options(const std::vector<PaymentCard> &);
    static PaymentCard read_card();
    static int display_payment_services();
    static void display_itinerary(const Itinerary &);
    static void display_itineraries(const std::vector<Itinerary> &);
    virtual ~FrontEnd()
    {
        delete reader;
        reader = nullptr;
    }
};
#endif // __FRONTEND_H__