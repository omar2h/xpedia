#include "backEnd.h"
#include "database.h"
#include "flightRequest.h"
#include "frontEnd.h"
#include "flightsManagerFactory.h"
#include "reservationRequestFactory.h"
#include "reservationFactory.h"
#include "customer.h"
#include "paymentFactory.h"
#include "idGenerator.h"
#include <iostream>
#include <typeinfo>
class ItineraryItem;

void BackEnd::save_user_in_db(User &user)
{
    try
    {
        Database::get_database()->save_user(user);
    }
    catch (int e)
    {
        throw e;
    }
}

User BackEnd::user_login(const std::string &email, const std::string &password)
{
    std::vector<User> users{};
    users = Database::get_database()->get_users(USERS_JSON);

    for (const auto &usr : users)
    {
        if (usr.getEmail() == email && usr.getPassword() == password)
            return usr;
    }
    throw 5;
}

// std::vector<Flight> BackEnd::get_available_flights(const FlightRequest &request)
// {
//     std::vector<Flight> flights;

//     for (FlightsManager *manager : flightsManagers)
//     {
//         manager->setFlightRequest(request);
//         std::vector<Flight> airlineFlights = manager->search_flights();

//         flights.insert(flights.end(), airlineFlights.begin(), airlineFlights.end());
//     }
//     return flights;
// }

std::vector<ItineraryItem *> BackEnd::get_available_reservations(ReservationRequest *request, RequestType requestType)
{
    std::vector<ItineraryItem *> items;
    std::vector<ItineraryManager *> managers;
    if (requestType == RequestType::flight)
    {
        managers = FlightsManagerFactory::getManagers();
        for (auto manager : managers)
        {
            manager->setRequest(request);
            std::vector<ItineraryItem *> airlineFlights = manager->search_reservations();
            items.insert(items.end(), airlineFlights.begin(), airlineFlights.end());
        }
    }
    return items;
}

void BackEnd::add_card(Customer &customer)
{
    PaymentCard card = FrontEnd::read_card();
    customer.addCard(card);
    Database::get_database()->update_customer_info(customer);
}

int BackEnd::select_card(Customer &customer)
{
    int choice{};
    while (true)
    {
        choice = FrontEnd::display_payment_options(customer.getCards());
        if (choice == -1)
            return -1;
        if (choice == 0)
            add_card(customer);
        else
            break;
    }
    return choice;
}

bool BackEnd::withdraw_money(const PaymentCard &card, int service, const Itinerary &currItinerary)
{
    PaymentStrategy *paymentStrategy = PaymentFactory::getPaymentService(static_cast<PaymentService>(service - 1));
    return paymentStrategy->pay(card, currItinerary.total_cost());
}

bool BackEnd::confirm_reservations(Customer &customer, const Itinerary &currItinerary)
{
    ItineraryManagerFactory factory;
    ItineraryManager *manager{};

    std::vector<Reservation *> reservations = currItinerary.getReservations();
    for (Reservation *res : reservations)
    {
        manager = factory.getManager(res->getType());
        if (!manager->reserve(res))
            return false;
    }
    return true;
}

int BackEnd::make_reservations(Customer &customer, const Itinerary &currItinerary)
{
    int choice = select_card(customer);
    if (choice == -1)
        return -1;
    std::cout << "line 120\n";
    PaymentCard card = customer.getCards()[choice - 1];
    choice = FrontEnd::display_payment_services();
    if (choice == -1)
        return choice;

    bool isPaid = withdraw_money(card, choice, currItinerary);
    if (isPaid)
        std::cout << "Transaction Succeeded\n";
    else
    {
        std::cout << "Transaction Failed\n";
        return -1;
    }

    return confirm_reservations(customer, currItinerary);
}

void BackEnd::payItinerary(const Itinerary &currItinerary, const User &user)
{
    if (!currItinerary.getReservations().size())
        throw 5; // no reservations
    Customer customer = Database::get_database()->getCustomer(user);
    std::cout << "line 81\n";
    int isConfirmed = make_reservations(customer, currItinerary);
    if (isConfirmed == 1)
    {
        std::cout << "Reservation is Confirmed\n";
        Database::get_database()->save_itinerary(customer.getId(), currItinerary);
        Database::get_database()->update_customer_info(customer);
        return;
    }
    else if (isConfirmed == 0)
    {
        std::cout << "Reservation Failed, Itinerary Cancelled\n";
    }
    return;
}

void BackEnd::add_flight(RequestType requestType, Itinerary &currItinerary)
{
    ReservationRequest *request = ReservationRequestFactory::getRequest(requestType);
    FrontEnd::read_request_data(request, requestType);
    std::vector<ItineraryItem *> items = get_available_reservations(request, requestType);
    int choice = FrontEnd::read_reservation_choice(items);
    if (choice == -1)
        return;
    Reservation *reservation = ReservationFactory::getRequest(requestType);
    reservation->setItem(items[choice - 1]);
    reservation->setRequest(request);
    currItinerary.add_item(reservation);
}

void BackEnd::create_itinerary(User &user)
{
    std::unordered_set<std::string> ids{};
    Itinerary currItinerary{IdGenerator::generate_id(ids)};

    while (true)
    {
        int choice{};
        choice = FrontEnd::display_create_itinerary_menu();
        if (choice == 1)
        {
            add_flight(RequestType::flight, currItinerary);
        }
        else if (choice == 2)
        {
            // add hotel
            ;
        }
        else if (choice == 3)
        {
            std::cout << currItinerary.toString() << "\n";
            payItinerary(currItinerary, user);
            currItinerary.Clear();
        }
        else if (choice == 4)
        {
            currItinerary.Clear();
            return;
        }
    }
}
