#include "backEnd.h"
#include "../db/database.h"
#include "../model/flightRequest.h"
#include "../frontend/frontEnd.h"
#include "../db/factories/flightsManagerFactory.h"
#include "../db/factories/hotelsManagerFactory.h"
#include "../db/factories/reservationRequestFactory.h"
#include "../db/factories/reservationFactory.h"
#include "../db/factories/paymentFactory.h"
#include "../db/idGenerator.h"
#include "../error.h"
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
    try
    {
        users = Database::get_database()->get_users(USERS_JSON);
    }
    catch (int e)
    {
        throw e;
    }

    for (const auto &usr : users)
    {
        if (usr.getEmail() == email && usr.getPassword() == password)
            return usr;
    }
    // invalid email/password
    throw 5;
}

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
    else if (requestType == RequestType::hotel)
    {
        managers = HotelsManagerFactory::getManagers();
        std::cout << "backend line 80" << managers.size() << "\n";
        for (auto manager : managers)
        {
            manager->setRequest(request);
            std::vector<ItineraryItem *> hotelRooms = manager->search_reservations();
            items.insert(items.end(), hotelRooms.begin(), hotelRooms.end());
        }
    }

    return items;
}

void BackEnd::add_card(Customer &customer)
{
    PaymentCard card = FrontEnd::read_card();
    customer.addCard(card);
    try
    {
        Database::get_database()->update_customer_info(customer);
    }
    catch (int e)
    {
        throw e;
    }
}

int BackEnd::select_card(Customer &customer)
{
    int choice{};
    while (true)
    {
        choice = FrontEnd::display_payment_options(customer.getCards());
        // cancel
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
    bool isPaid = paymentStrategy->pay(card, currItinerary.total_cost());
    delete paymentStrategy;
    paymentStrategy = nullptr;
    return isPaid;
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
        {
            delete manager;
            manager = nullptr;
            return false;
        }
    }
    delete manager;
    manager = nullptr;
    return true;
}

int BackEnd::make_reservations(Customer &customer, const Itinerary &currItinerary)
{
    int choice = select_card(customer);
    // cancel
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
        throw 6; // no reservations
    Customer customer;
    try
    {
        customer = Database::get_database()->getCustomer(user);
    }
    catch (int e)
    {
        throw e;
    }
    std::cout << "line 81"
              << "\n";
    int isConfirmed = make_reservations(customer, currItinerary);
    if (isConfirmed == 1)
    {
        std::cout << "Reservation is Confirmed\n";
        Database::get_database()->save_itinerary(customer.getId(), currItinerary);
        customer.addItineraryId(currItinerary.getId());
        try
        {
            Database::get_database()->update_customer_info(customer);
        }
        catch (int e)
        {
            throw e;
        }
        return;
    }
    else if (isConfirmed == 0)
    {
        std::cout << "Reservation Failed, Itinerary Cancelled\n";
    }
    return;
}

void BackEnd::add_new_item(RequestType requestType, Itinerary &currItinerary)
{
    ReservationRequest *request = ReservationRequestFactory::getRequest(requestType);
    FrontEnd::read_request_data(request, requestType);
    std::vector<ItineraryItem *> items = get_available_reservations(request, requestType);
    int choice = FrontEnd::read_reservation_choice(items);
    // cancel
    if (choice == -1)
        return;
    Reservation *reservation = ReservationFactory::getReservation(requestType);
    reservation->setItem(items[choice - 1]);
    reservation->setRequest(request);
    currItinerary.add_item(reservation);
}

void BackEnd::list_itineraries(const User &user)
{
    bool isCustomer;
    try
    {
        isCustomer = Database::get_database()->check_user_is_customer(user);
    }
    catch (int e)
    {
        Error::display_error(e);
        return;
    }
    if (!isCustomer)
    {
        std::cout << "User has no Itineraries\n";
        return;
    }
    Customer customer;
    try
    {
        customer = Database::get_database()->getCustomer(user);
    }
    catch (int e)
    {
        Error::display_error(e);
        return;
    }
    if ((int)customer.getItinerariesIds().size() == 0)
    {
        std::cout << "User has no Itineraries\n";
        return;
    }
    try
    {
        std::vector<Itinerary> customerItineraries = Database::get_database()->getCustomerItineraries(customer.getId());
        FrontEnd::display_itineraries(customerItineraries);
    }
    catch (int e)
    {
        Error::display_error(e);
        return;
    }
}

void BackEnd::create_itinerary(User &user)
{
    std::unordered_set<std::string> ids{};
    Itinerary currItinerary;

    while (true)
    {
        currItinerary.setId(IdGenerator::generate_id(ids));
        int choice{};
        choice = FrontEnd::display_create_itinerary_menu();
        if (choice == 1)
        {
            add_new_item(RequestType::flight, currItinerary);
        }
        else if (choice == 2)
        {
            add_new_item(RequestType::hotel, currItinerary);
        }
        else if (choice == 3)
        {
            std::cout << currItinerary.toString() << "\n";
            try
            {
                payItinerary(currItinerary, user);
            }
            catch (int e)
            {
                Error::display_error(e);
                currItinerary.Clear();
                continue;
            }
            currItinerary.Clear();
            return;
        }
        else if (choice == 4)
        {
            currItinerary.Clear();
            return;
        }
    }
}
