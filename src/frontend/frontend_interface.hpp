#pragma once

#include "../model/payment_card.hpp"
#include "../model/itinerary.hpp"
#include "../model/requests/reservation_request.hpp"
#include "../model/user.hpp"
#include <vector>

class ItineraryItem;

class IFrontend
{
public:
    virtual ~IFrontend() = default;
    virtual int display_create_itinerary_menu() = 0;
    virtual void read_request_data(ReservationRequest &, RequestType) = 0;
    virtual int read_reservation_choice(const std::vector<ItineraryItem *> &) = 0;
    virtual int display_payment_options(const std::vector<PaymentCard> &) = 0;
    virtual PaymentCard read_card() = 0;
    virtual int display_payment_services() = 0;
    virtual void display_itineraries(const std::vector<Itinerary> &) = 0;
    virtual int show_start_menu() = 0;
    virtual void display_welcome_message(const std::string &, const std::string &) = 0;
    virtual int display_main_menu() = 0;
    virtual void display_user_profile(const User &) = 0;
    virtual User login() = 0;
    virtual void signup() = 0;
};