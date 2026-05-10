#include "console_frontend.hpp"
#include "frontend.hpp"

int ConsoleFrontend::display_create_itinerary_menu()
{
    return Frontend::display_create_itinerary_menu();
}

void ConsoleFrontend::read_request_data(ReservationRequest &req, RequestType type)
{
    Frontend::read_request_data(req, type);
}

int ConsoleFrontend::read_reservation_choice(const std::vector<ItineraryItem *> &items)
{
    return Frontend::read_reservation_choice(items);
}

int ConsoleFrontend::display_payment_options(const std::vector<PaymentCard> &cards)
{
    return Frontend::display_payment_options(cards);
}

PaymentCard ConsoleFrontend::read_card()
{
    return Frontend::read_card();
}

int ConsoleFrontend::display_payment_services()
{
    return Frontend::display_payment_services();
}

void ConsoleFrontend::display_itineraries(const std::vector<Itinerary> &itineraries)
{
    Frontend::display_itineraries(itineraries);
}