#pragma once

#include "../model/user.hpp"
#include "providers/flight_provider.hpp"
#include "../model/itinerary.hpp"
#include "../model/customer.hpp"
#include "payments/payment_strategy.hpp"
#include "frontend_interface.hpp"
#include "database_interface.hpp"
#include "factories/reservation_provider_factory.hpp"
#include "factories/payment_factory.hpp"
class ReservationRequestFactory;
class ReservationFactory;

class Application
{
    IDatabase &m_database;
    ReservationProviderFactory &m_flightProviderFactory;
    ReservationProviderFactory &m_hotelProviderFactory;
    ReservationProviderFactory &m_reservationProviderFactory;
    IPaymentFactory &m_paymentFactory;
    ReservationRequestFactory &m_requestFactory;
    ReservationFactory &m_reservationFactory;

public:
    Application(IDatabase &database,
                ReservationProviderFactory &flightProviderFactory,
                ReservationProviderFactory &hotelProviderFactory,
                ReservationProviderFactory &reservationProviderFactory,
                IPaymentFactory &paymentFactory,
                ReservationRequestFactory &requestFactory,
                ReservationFactory &reservationFactory);

    void saveUserInDb(User &);
    [[nodiscard]] User userLogin(const std::string &, const std::string &);
    void createItinerary(User &, IFrontend &);
    void addNewItem(RequestType, Itinerary &, IFrontend &);
    [[nodiscard]] std::vector<std::unique_ptr<ItineraryItem>> getAvailableReservations(ReservationRequest *, RequestType);
    [[nodiscard]] int makeReservations(Customer &, const Itinerary &, IFrontend &);
    [[nodiscard]] bool confirmReservations(Customer &customer, const Itinerary &currItinerary);
    [[nodiscard]] bool withdrawMoney(const PaymentCard &card, int service, const Itinerary &currItinerary);
    [[nodiscard]] int selectCard(Customer &customer, IFrontend &);
    void payItinerary(const Itinerary &, const User &, IFrontend &);
    void addCard(Customer &, IFrontend &);
    void listItineraries(const User &, IFrontend &);
};
