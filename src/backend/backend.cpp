#include "backend.hpp"
#include "../db/database.hpp"
#include "../model/requests/flight_request.hpp"
#include "../frontend/frontend_interface.hpp"
#include "factories/flights_manager_factory.hpp"
#include "factories/hotels_manager_factory.hpp"
#include "../model/factories/reservation_request_factory.hpp"
#include "../model/factories/reservation_factory.hpp"
#include "factories/payment_factory.hpp"
#include "../db/id_generator.hpp"
#include "../error.hpp"
#include <iostream>
#include <typeinfo>
class ItineraryItem;

void Backend::save_user_in_db(User &user)
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

User Backend::user_login(const std::string &email, const std::string &password)
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
    throw 5;
}

std::vector<ItineraryItem *> Backend::get_available_reservations(ReservationRequest *request, RequestType requestType)
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
        for (auto manager : managers)
        {
            manager->setRequest(request);
            std::vector<ItineraryItem *> hotelRooms = manager->search_reservations();
            items.insert(items.end(), hotelRooms.begin(), hotelRooms.end());
        }
    }

    return items;
}

void Backend::add_card(Customer &customer, IFrontend &frontend)
{
    PaymentCard card = frontend.read_card();
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

int Backend::select_card(Customer &customer, IFrontend &frontend)
{
    int choice{};
    while (true)
    {
        choice = frontend.display_payment_options(customer.getCards());
        if (choice == -1)
            return -1;
        if (choice == 0)
            add_card(customer, frontend);
        else
            break;
    }
    return choice;
}

bool Backend::withdraw_money(const PaymentCard &card, int service, const Itinerary &currItinerary)
{
    PaymentStrategy *paymentStrategy = PaymentFactory::getPaymentService(static_cast<PaymentService>(service - 1));
    bool isPaid = paymentStrategy->pay(card, currItinerary.total_cost());
    delete paymentStrategy;
    paymentStrategy = nullptr;
    return isPaid;
}

bool Backend::confirm_reservations(Customer &customer, const Itinerary &currItinerary)
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

int Backend::make_reservations(Customer &customer, const Itinerary &currItinerary, IFrontend &frontend)
{
    int choice = select_card(customer, frontend);
    if (choice == -1)
        return -1;
    PaymentCard card = customer.getCards()[choice - 1];
    choice = frontend.display_payment_services();
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

void Backend::payItinerary(const Itinerary &currItinerary, const User &user, IFrontend &frontend)
{
    if (!currItinerary.getReservations().size())
        throw 6;
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
    int isConfirmed = make_reservations(customer, currItinerary, frontend);
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

void Backend::add_new_item(RequestType requestType, Itinerary &currItinerary, IFrontend &frontend)
{
    auto request = ReservationRequestFactory::getRequest(requestType);
    ReservationRequest *requestPtr = request.get();
    frontend.read_request_data(*requestPtr, requestType);
    std::vector<ItineraryItem *> items = get_available_reservations(request.get(), requestType);
    int choice = frontend.read_reservation_choice(items);
    if (choice == -1)
        return;
    auto reservation = ReservationFactory::getReservation(requestType);
    reservation->setItem(items[choice - 1]);
    reservation->setRequest(request.get());
    currItinerary.add_item(std::move(reservation));
}

void Backend::list_itineraries(const User &user, IFrontend &frontend)
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
        frontend.display_itineraries(customerItineraries);
    }
    catch (int e)
    {
        Error::display_error(e);
        return;
    }
}

void Backend::create_itinerary(User &user, IFrontend &frontend)
{
    std::unordered_set<std::string> ids{};
    Itinerary currItinerary;

    while (true)
    {
        currItinerary.setId(IdGenerator::generate_id(ids));
        int choice{};
        choice = frontend.display_create_itinerary_menu();
        if (choice == 1)
        {
            add_new_item(RequestType::flight, currItinerary, frontend);
        }
        else if (choice == 2)
        {
            add_new_item(RequestType::hotel, currItinerary, frontend);
        }
        else if (choice == 3)
        {
            std::cout << currItinerary.toString() << "\n";
            try
            {
                payItinerary(currItinerary, user, frontend);
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
