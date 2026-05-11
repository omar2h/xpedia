#include "console_frontend.hpp"
#include "printer.hpp"
#include "input_handler.hpp"
#include "../model/requests/flight_request.hpp"
#include "../model/requests/hotel_request.hpp"
#include "../model/itinerary_item.hpp"
#include "../model/itinerary.hpp"
#include "login_handler.hpp"
#include "signup_handler.hpp"
#include <iostream>

ConsoleFrontend::ConsoleFrontend(Application &backend, LoginHandler &loginHandler, SignupHandler &signupHandler)
    : m_application(backend), m_loginHandler(loginHandler), m_signupHandler(signupHandler) {}

int ConsoleFrontend::displayCreateItineraryMenu()
{
    std::vector<std::string> menu{
        "Add Flight",
        "Add Hotel",
        "Check Out",
        "Cancel"};

    int menuCount{(int)menu.size()};

    while (true)
    {
        Printer::printMenu(menu);

        try
        {
            return InputHandler::getChoice(1, menuCount);
        }
        catch (const std::exception &e)
        {
            showError(e.what());
        }
    }
}

void ConsoleFrontend::readRequestData(ReservationRequest &request, RequestType type)
{
    if (type == RequestType::flight)
    {
        readFlightRequestData(dynamic_cast<FlightRequest &>(request));
    }
    else if (type == RequestType::hotel)
    {
        readHotelRequestData(dynamic_cast<HotelRequest &>(request));
    }
}

int ConsoleFrontend::readReservationChoice(const std::vector<std::unique_ptr<ItineraryItem>> &items)
{
    std::vector<std::string> options{};

    for (const auto &item : items)
    {
        options.push_back(item->toString());
    }

    int itemsCount{(int)items.size()};

    while (true)
    {
        Printer::printOptions(options);

        std::cout << "Enter choice(-1 to cancel): ";

        try
        {
            return InputHandler::getChoice(1, itemsCount);
        }
        catch (const std::exception &e)
        {
            showError(e.what());
        }
    }
}

int ConsoleFrontend::displayPaymentOptions(const std::vector<PaymentCard> &cards)
{
    std::vector<std::string> options;

    for (const auto &card : cards)
    {
        options.push_back(card.toString());
    }

    int cardsCount{(int)cards.size()};

    while (true)
    {
        Printer::printOptions(options);

        std::cout << "Enter choice(0 to add card, -1 to cancel): ";

        try
        {
            return InputHandler::getChoice(0, cardsCount);
        }
        catch (const std::exception &e)
        {
            showError(e.what());
        }
    }
}

PaymentCard ConsoleFrontend::readCard()
{
    std::string number;
    std::string owner;
    std::string date;
    std::string ccv;
    std::cout << "Enter Card Number: ";
    std::cin >> number;
    std::cout << "Enter Card Owner: ";
    std::cin >> owner;
    std::cout << "Enter Catd Expiry Date: ";
    std::cin >> date;
    std::cout << "Enter Card CCV: ";
    std::cin >> ccv;

    return {number, owner, date, ccv};
}

int ConsoleFrontend::displayPaymentServices()
{
    std::vector<std::string> services{
        "Paypal",
        "Stripe",
        "Square"};

    int count{(int)services.size()};

    while (true)
    {
        std::cout << "Payment Services:\n";

        Printer::printOptions(services);

        std::cout << "Enter choice(-1 to cancel): ";

        try
        {
            return InputHandler::getChoice(1, count);
        }
        catch (const std::exception &e)
        {
            showError(e.what());
        }
    }
}

void ConsoleFrontend::displayItineraries(const std::vector<Itinerary> &itineraries)
{
    int count{(int)itineraries.size()};
    std::cout << count << " itineraries\n";
    for (int i = 0; i < count; i++)
    {
        std::cout << i + 1 << "- ";
        displayItinerary(itineraries[i]);
        std::cout << "\n";
    }
}

void ConsoleFrontend::displayItinerary(const Itinerary &itinerary)
{
    const auto &reservations = itinerary.getReservations();
    int count{(int)reservations.size()};
    std::cout << "Itinerary of " << count << " reservations\n";
    std::cout << itinerary.toSummaryString() << "\n";
}

void ConsoleFrontend::readFlightRequestData(FlightRequest &request)
{
    std::string from{};
    std::string to{};
    std::string date{};
    int adults{};
    int children{};

    std::cout << "Enter From City: ";
    std::cin >> from;
    std::cout << "Enter To City: ";
    std::cin >> to;
    std::cout << "Enter Date: ";
    std::cin >> date;
    std::cout << "Enter Adults: ";
    std::cin >> adults;
    std::cout << "Enter Children: ";
    std::cin >> children;

    request.setFromCity(from);
    request.setToCity(to);
    request.setDate(date);
    request.setAdults(adults);
    request.setChildren(children);
}

void ConsoleFrontend::readHotelRequestData(HotelRequest &request)
{
    std::string city{};
    std::string fromDate{};
    std::string toDate{};
    int adults{};
    int children{};
    int rooms{};

    std::cout << "Enter City: ";
    std::cin >> city;
    std::cout << "Enter From Date: ";
    std::cin >> fromDate;
    std::cout << "Enter To Date: ";
    std::cin >> toDate;
    std::cout << "Enter Adults: ";
    std::cin >> adults;
    std::cout << "Enter Children: ";
    std::cin >> children;
    std::cout << "Enter Rooms: ";
    std::cin >> rooms;

    request.setCity(city);
    request.setFromDate(fromDate);
    request.setToDate(toDate);
    request.setAdults(adults);
    request.setChildren(children);
    request.setRooms(rooms);
}

int ConsoleFrontend::showStartMenu()
{
    std::vector<std::string> startMenu{
        "Login",
        "SignUp",
        "Exit"};

    while (true)
    {
        Printer::printMenu(startMenu);

        try
        {
            return InputHandler::getChoice(1, 3);
        }
        catch (const std::exception &e)
        {
            showError(e.what());
        }
    }
}

void ConsoleFrontend::displayWelcomeMessage(const std::string &firstName, const std::string &lastName)
{
    std::cout << "Welcome " << firstName << " " << lastName << "\n\n";
}

int ConsoleFrontend::displayMainMenu()
{
    std::vector<std::string> startMenu{
        "View Profile",
        "Create Itinerary",
        "List My Itineraries",
        "Logout"};

    int menuCount{(int)startMenu.size()};

    while (true)
    {
        Printer::printMenu(startMenu);

        try
        {
            return InputHandler::getChoice(1, menuCount);
        }
        catch (const std::exception &e)
        {
            showError(e.what());
        }
    }
}

void ConsoleFrontend::displayUserProfile(const User &user)
{
    std::cout << "\n";
    std::cout << "Name: " << user.getFirstName() << " " << user.getLastName() << "\n";
    std::cout << "Email: " << user.getEmail() << "\n";
    std::cout << "Phone: " << user.getPhone() << "\n";
    std::cout << "\n";
}

User ConsoleFrontend::login()
{
    while (true)
    {
        try
        {
            return m_loginHandler.login();
        }
        catch (const std::exception &e)
        {
            showError(e.what());
        }
    }
}

void ConsoleFrontend::signup()
{
    while (true)
    {
        try
        {
            m_signupHandler.signup();
            return;
        }
        catch (const std::exception &e)
        {
            showError(e.what());
        }
    }
}

void ConsoleFrontend::showMessage(const std::string &msg)
{
    std::cout << msg << "\n";
}

void ConsoleFrontend::showError(const std::string &msg)
{
    std::cout << msg << "\n";
}