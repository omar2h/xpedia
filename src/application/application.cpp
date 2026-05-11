#include "application.hpp"
#include "../db/database.hpp"
#include "../model/requests/flight_request.hpp"
#include "../frontend/frontend_interface.hpp"
#include "factories/flight_provider_factory.hpp"
#include "factories/hotel_provider_factory.hpp"
#include "../model/factories/reservation_request_factory.hpp"
#include "../model/factories/reservation_factory.hpp"
#include "factories/payment_factory.hpp"
#include "../db/id_generator.hpp"
#include "../error.hpp"
#include <iostream>
#include <typeinfo>
class ItineraryItem;

Application::Application(Database &database,
                         FlightProviderFactory &flightProviderFactory,
                         HotelProviderFactory &hotelProviderFactory,
                         ReservationProviderFactory &reservationProviderFactory)
    : m_database(database),
      m_flightProviderFactory(flightProviderFactory),
      m_hotelProviderFactory(hotelProviderFactory),
      m_reservationProviderFactory(reservationProviderFactory) {}

void Application::saveUserInDb(User &user)
{
    m_database.saveUser(user);
}

User Application::userLogin(const std::string &email, const std::string &password)
{
    std::vector<User> users = m_database.getUsers("users.json");

    for (const auto &usr : users)
    {
        if (usr.getEmail() == email && usr.getPassword() == password)
            return usr;
    }

    throw std::runtime_error("Invalid email/password");
}

void Application::addCard(Customer &customer, IFrontend &frontend)
{
    PaymentCard card = frontend.readCard();
    customer.addCard(card);

    m_database.updateCustomerInfo(customer);
}

int Application::makeReservations(Customer &customer, const Itinerary &currItinerary, IFrontend &frontend)
{
    int choice = selectCard(customer, frontend);

    if (choice == -1)
        return -1;

    PaymentCard card = customer.getCards()[choice - 1];

    choice = frontend.displayPaymentServices();

    if (choice == -1)
        return choice;

    bool isPaid = withdrawMoney(card, choice, currItinerary);

    if (isPaid)
        frontend.showMessage("Transaction Succeeded");
    else
    {
        frontend.showError("Transaction Failed");
        return -1;
    }

    return confirmReservations(customer, currItinerary);
}

void Application::payItinerary(const Itinerary &currItinerary, const User &user, IFrontend &frontend)
{
    if (currItinerary.getReservations().empty())
        throw std::runtime_error("No Reservations to Pay");

    Customer customer = m_database.getCustomer(user);

    int isConfirmed = makeReservations(customer, currItinerary, frontend);

    if (isConfirmed == 1)
    {
        frontend.showMessage("Reservation is Confirmed");

        m_database.saveItinerary(customer.getId(), currItinerary);

        customer.addItineraryId(currItinerary.getId());

        m_database.updateCustomerInfo(customer);

        return;
    }

    if (isConfirmed == 0)
        frontend.showError("Reservation Failed, Itinerary Cancelled");
}

void Application::addNewItem(RequestType requestType, Itinerary &currItinerary, IFrontend &frontend)
{
    auto request = ReservationRequestFactory::getRequest(requestType);

    frontend.readRequestData(*request, requestType);

    std::vector<std::unique_ptr<ItineraryItem>> items = getAvailableReservations(request.get(), requestType);

    int choice = frontend.readReservationChoice(items);

    if (choice == -1)
        return;

    auto reservation = ReservationFactory::getReservation(requestType);

    reservation->setItem(items[choice - 1].get());
    reservation->setRequest(std::move(request));

    currItinerary.addItem(std::move(reservation));
}

void Application::listItineraries(const User &user, IFrontend &frontend)
{
    bool isCustomer = m_database.checkUserIsCustomer(user);

    if (!isCustomer)
    {
        frontend.showMessage("User has no itineraries");
        return;
    }

    Customer customer = m_database.getCustomer(user);

    if (customer.getItinerariesIds().empty())
    {
        frontend.showMessage("User has no itineraries");
        return;
    }

    std::vector<Itinerary> customerItineraries = m_database.getCustomerItineraries(customer.getId());

    frontend.displayItineraries(customerItineraries);
}

void Application::createItinerary(User &user, IFrontend &frontend)
{
    std::unordered_set<std::string> ids{};
    Itinerary currItinerary;

    while (true)
    {
        currItinerary.setId(IdGenerator::generateId(ids));

        int choice = frontend.displayCreateItineraryMenu();

        if (choice == 1)
        {
            addNewItem(RequestType::flight, currItinerary, frontend);
        }
        else if (choice == 2)
        {
            addNewItem(RequestType::hotel, currItinerary, frontend);
        }
        else if (choice == 3)
        {
            frontend.displayItinerary(currItinerary);

            payItinerary(currItinerary, user, frontend);

            currItinerary.clear();
            return;
        }
        else if (choice == 4)
        {
            currItinerary.clear();
            return;
        }
    }
}

std::vector<std::unique_ptr<ItineraryItem>> Application::getAvailableReservations(ReservationRequest *request, RequestType requestType)
{
    std::vector<std::unique_ptr<ItineraryItem>> items;
    std::vector<std::unique_ptr<ReservationProvider>> providers;

    if (requestType == RequestType::flight)
    {
        providers = m_flightProviderFactory.getProviders();

        for (auto &provider : providers)
        {
            provider->setRequest(request);

            std::vector<std::unique_ptr<ItineraryItem>> airlineFlights = provider->searchReservations();

            items.insert(items.end(),
                         std::make_move_iterator(airlineFlights.begin()),
                         std::make_move_iterator(airlineFlights.end()));
        }
    }
    else if (requestType == RequestType::hotel)
    {
        providers = m_hotelProviderFactory.getProviders();

        for (auto &provider : providers)
        {
            provider->setRequest(request);

            std::vector<std::unique_ptr<ItineraryItem>> hotelRooms = provider->searchReservations();

            items.insert(items.end(),
                         std::make_move_iterator(hotelRooms.begin()),
                         std::make_move_iterator(hotelRooms.end()));
            ;
        }
    }

    return items;
}

int Application::selectCard(Customer &customer, IFrontend &frontend)
{
    int choice{};

    while (true)
    {
        choice =
            frontend.displayPaymentOptions(customer.getCards());

        if (choice == -1)
            return -1;

        if (choice == 0)
            addCard(customer, frontend);
        else
            break;
    }

    return choice;
}

bool Application::withdrawMoney(
    const PaymentCard &card,
    int service,
    const Itinerary &currItinerary)
{
    auto paymentStrategy = PaymentFactory::getPaymentService(static_cast<PaymentService>(service - 1));
    bool isPaid = paymentStrategy->pay(card, currItinerary.total_cost());
    return isPaid;
}

bool Application::confirmReservations(Customer &customer, const Itinerary &currItinerary)
{
    std::unique_ptr<ReservationProvider> provider{};

    const auto &reservations = currItinerary.getReservations();

    for (const auto &res : reservations)
    {
        provider = m_reservationProviderFactory.getProvider(res->getType());

        if (!provider->reserve(res.get()))
        {
            return false;
        }
    }
    return true;
}
