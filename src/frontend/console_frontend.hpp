#pragma once

#include "frontend_interface.hpp"

class ConsoleFrontend : public IFrontend
{
public:
    int display_create_itinerary_menu() override;
    void read_request_data(ReservationRequest *&, RequestType) override;
    int read_reservation_choice(const std::vector<ItineraryItem *> &) override;
    int display_payment_options(const std::vector<PaymentCard> &) override;
    PaymentCard read_card() override;
    int display_payment_services() override;
    void display_itineraries(const std::vector<Itinerary> &) override;
};