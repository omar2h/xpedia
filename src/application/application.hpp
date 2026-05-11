#pragma once

#include "../model/user.hpp"
#include "providers/flight_provider.hpp"
#include "../model/itinerary.hpp"
#include "../model/customer.hpp"
#include "payments/payment_strategy.hpp"
#include "../frontend/frontend_interface.hpp"

class Database;
class FlightProviderFactory;
class HotelProviderFactory;
class ReservationProviderFactory;

class Application
{
    Database &m_database;
    FlightProviderFactory &m_flightProviderFactory;
    HotelProviderFactory &m_hotelProviderFactory;
    ReservationProviderFactory &m_reservationProviderFactory;

public:
    Application(Database &database,
                FlightProviderFactory &flightProviderFactory,
                HotelProviderFactory &hotelProviderFactory,
                ReservationProviderFactory &reservationProviderFactory);

    void saveUserInDb(User &);
    User userLogin(const std::string &, const std::string &);
    void createItinerary(User &, IFrontend &);
    void addNewItem(RequestType, Itinerary &, IFrontend &);
    std::vector<std::unique_ptr<ItineraryItem>> getAvailableReservations(ReservationRequest *, RequestType);
    int makeReservations(Customer &, const Itinerary &, IFrontend &);
    bool confirmReservations(Customer &customer, const Itinerary &currItinerary);
    bool withdrawMoney(const PaymentCard &card, int service, const Itinerary &currItinerary);
    int selectCard(Customer &customer, IFrontend &);
    void payItinerary(const Itinerary &, const User &, IFrontend &);
    void addCard(Customer &, IFrontend &);
    void listItineraries(const User &, IFrontend &);
};
