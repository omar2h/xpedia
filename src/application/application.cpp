#include "application.hpp"
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

Application::Application(Database &database) : m_database(database) {}

void Application::save_user_in_db(User &user)
{
    m_database.save_user(user);
}

User Application::user_login(const std::string &email, const std::string &password)
{
    std::vector<User> users = m_database.get_users("users.json");

    for (const auto &usr : users)
    {
        if (usr.getEmail() == email && usr.getPassword() == password)
            return usr;
    }

    throw std::runtime_error("Invalid email/password");
}

void Application::add_card(Customer &customer, IFrontend &frontend)
{
    PaymentCard card = frontend.read_card();
    customer.addCard(card);

    m_database.update_customer_info(customer);
}

int Application::make_reservations(Customer &customer, const Itinerary &currItinerary, IFrontend &frontend)
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
        frontend.show_message("Transaction Succeeded");
    else
    {
        frontend.show_error("Transaction Failed");
        return -1;
    }

    return confirm_reservations(customer, currItinerary);
}

void Application::payItinerary(const Itinerary &currItinerary, const User &user, IFrontend &frontend)
{
    if (currItinerary.getReservations().empty())
        throw std::runtime_error("No Reservations to Pay");

    Customer customer = m_database.getCustomer(user);

    int isConfirmed = make_reservations(customer, currItinerary, frontend);

    if (isConfirmed == 1)
    {
        frontend.show_message("Reservation is Confirmed");

        m_database.save_itinerary(customer.getId(), currItinerary);

        customer.addItineraryId(currItinerary.getId());

        m_database.update_customer_info(customer);

        return;
    }

    if (isConfirmed == 0)
        frontend.show_error("Reservation Failed, Itinerary Cancelled");
}

void Application::add_new_item(RequestType requestType, Itinerary &currItinerary, IFrontend &frontend)
{
    auto request = ReservationRequestFactory::getRequest(requestType);

    frontend.read_request_data(*request, requestType);

    std::vector<std::unique_ptr<ItineraryItem>> items = get_available_reservations(request.get(), requestType);

    int choice = frontend.read_reservation_choice(items);

    if (choice == -1)
        return;

    auto reservation = ReservationFactory::getReservation(requestType);

    reservation->setItem(items[choice - 1].get());
    reservation->setRequest(std::move(request));

    currItinerary.add_item(std::move(reservation));
}

void Application::list_itineraries(const User &user, IFrontend &frontend)
{
    bool isCustomer = m_database.check_user_is_customer(user);

    if (!isCustomer)
    {
        frontend.show_message("User has no itineraries");
        return;
    }

    Customer customer = m_database.getCustomer(user);

    if (customer.getItinerariesIds().empty())
    {
        frontend.show_message("User has no itineraries");
        return;
    }

    std::vector<Itinerary> customerItineraries = m_database.getCustomerItineraries(customer.getId());

    frontend.display_itineraries(customerItineraries);
}

void Application::create_itinerary(User &user, IFrontend &frontend)
{
    std::unordered_set<std::string> ids{};
    Itinerary currItinerary;

    while (true)
    {
        currItinerary.setId(IdGenerator::generate_id(ids));

        int choice = frontend.display_create_itinerary_menu();

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
            frontend.display_itinerary(currItinerary);

            payItinerary(currItinerary, user, frontend);

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

std::vector<std::unique_ptr<ItineraryItem>> Application::get_available_reservations(ReservationRequest *request, RequestType requestType)
{
    std::vector<std::unique_ptr<ItineraryItem>> items;
    std::vector<std::unique_ptr<ItineraryManager>> managers;

    if (requestType == RequestType::flight)
    {
        managers = FlightsManagerFactory::getManagers();

        for (auto &manager : managers)
        {
            manager->setRequest(request);

            std::vector<std::unique_ptr<ItineraryItem>> airlineFlights = manager->search_reservations();

            items.insert(items.end(),
                         std::make_move_iterator(airlineFlights.begin()),
                         std::make_move_iterator(airlineFlights.end()));
        }
    }
    else if (requestType == RequestType::hotel)
    {
        managers = HotelsManagerFactory::getManagers();

        for (auto &manager : managers)
        {
            manager->setRequest(request);

            std::vector<std::unique_ptr<ItineraryItem>> hotelRooms = manager->search_reservations();

            items.insert(items.end(),
                         std::make_move_iterator(hotelRooms.begin()),
                         std::make_move_iterator(hotelRooms.end()));
            ;
        }
    }

    return items;
}

int Application::select_card(Customer &customer, IFrontend &frontend)
{
    int choice{};

    while (true)
    {
        choice =
            frontend.display_payment_options(customer.getCards());

        if (choice == -1)
            return -1;

        if (choice == 0)
            add_card(customer, frontend);
        else
            break;
    }

    return choice;
}

bool Application::withdraw_money(
    const PaymentCard &card,
    int service,
    const Itinerary &currItinerary)
{
    auto paymentStrategy = PaymentFactory::getPaymentService(static_cast<PaymentService>(service - 1));
    bool isPaid = paymentStrategy->pay(card, currItinerary.total_cost());
    return isPaid;
}

bool Application::confirm_reservations(Customer &customer, const Itinerary &currItinerary)
{
    ItineraryManagerFactory factory;

    std::unique_ptr<ItineraryManager> manager{};

    const auto &reservations = currItinerary.getReservations();

    for (const auto &res : reservations)
    {
        manager = factory.getManager(res->getType());

        if (!manager->reserve(res.get()))
        {
            return false;
        }
    }
    return true;
}
