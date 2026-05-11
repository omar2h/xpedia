#pragma once

#include "../model/user.hpp"
#include "../model/itinerary.hpp"
#include "../model/customer.hpp"
#include "frontend_interface.hpp"
#include "database_interface.hpp"
#include "services/reservation_service.hpp"
#include "services/payment_service.hpp"
class ReservationRequestFactory;
class ReservationFactory;

class Application
{
    IDatabase &m_database;
    ReservationService &m_reservationService;
    PaymentProcessor &m_paymentService;
    ReservationRequestFactory &m_requestFactory;
    ReservationFactory &m_reservationFactory;

public:
    Application(IDatabase &database,
                ReservationService &reservationService,
                PaymentProcessor &paymentService,
                ReservationRequestFactory &requestFactory,
                ReservationFactory &reservationFactory);

    void createItinerary(User &, IFrontend &);
    void addNewItem(RequestType, Itinerary &, IFrontend &);
    void payItinerary(const Itinerary &, const User &, IFrontend &);
    void addCard(Customer &, IFrontend &);
    void listItineraries(const User &, IFrontend &);
};
