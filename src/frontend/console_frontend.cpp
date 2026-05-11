#include "console_frontend.hpp"
#include "printer.hpp"
#include "input_handler.hpp"
#include "flight_request_data_reader.hpp"
#include "hotel_request_data_reader.hpp"
#include "../model/itinerary_item.hpp"
#include "../model/itinerary.hpp"
#include "login_handler.hpp"
#include "signup_handler.hpp"
#include <iostream>

ConsoleFrontend::ConsoleFrontend(Backend &backend, LoginHandler &loginHandler, SignupHandler &signupHandler)
    : m_backend(backend), m_loginHandler(loginHandler), m_signupHandler(signupHandler) {}

int ConsoleFrontend::display_create_itinerary_menu()
{
    std::vector<std::string> menu{
        "Add Flight",
        "Add Hotel",
        "Check Out",
        "Cancel"};

    int menuCount{(int)menu.size()};

    while (true)
    {
        Printer::print_menu(menu);

        try
        {
            return InputHandler::get_choice(1, menuCount);
        }
        catch (const std::exception &e)
        {
            show_error(e.what());
        }
    }
}

void ConsoleFrontend::read_request_data(ReservationRequest &request, RequestType type)
{
    if (type == RequestType::flight)
    {
        read_flight_request_data(dynamic_cast<FlightRequest &>(request));
    }
    else if (type == RequestType::hotel)
    {
        read_hotel_request_data(dynamic_cast<HotelRequest &>(request));
    }
}

int ConsoleFrontend::read_reservation_choice(const std::vector<std::unique_ptr<ItineraryItem>> &items)
{
    std::vector<std::string> options{};

    for (const auto &item : items)
    {
        options.push_back(item->toString());
    }

    int itemsCount{(int)items.size()};

    while (true)
    {
        Printer::print_options(options);

        std::cout << "Enter choice(-1 to cancel): ";

        try
        {
            return InputHandler::get_choice(1, itemsCount);
        }
        catch (const std::exception &e)
        {
            show_error(e.what());
        }
    }
}

int ConsoleFrontend::display_payment_options(const std::vector<PaymentCard> &cards)
{
    std::vector<std::string> options;

    for (const auto &card : cards)
    {
        options.push_back(card.toString());
    }

    int cardsCount{(int)cards.size()};

    while (true)
    {
        Printer::print_options(options);

        std::cout << "Enter choice(0 to add card, -1 to cancel): ";

        try
        {
            return InputHandler::get_choice(0, cardsCount);
        }
        catch (const std::exception &e)
        {
            show_error(e.what());
        }
    }
}

PaymentCard ConsoleFrontend::read_card()
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

int ConsoleFrontend::display_payment_services()
{
    std::vector<std::string> services{
        "Paypal",
        "Stripe",
        "Square"};

    int count{(int)services.size()};

    while (true)
    {
        std::cout << "Payment Services:\n";

        Printer::print_options(services);

        std::cout << "Enter choice(-1 to cancel): ";

        try
        {
            return InputHandler::get_choice(1, count);
        }
        catch (const std::exception &e)
        {
            show_error(e.what());
        }
    }
}

void ConsoleFrontend::display_itineraries(const std::vector<Itinerary> &itineraries)
{
    int count{(int)itineraries.size()};
    std::cout << count << " itineraries\n";
    for (int i = 0; i < count; i++)
    {
        std::cout << i + 1 << "- ";
        display_itinerary(itineraries[i]);
        std::cout << "\n";
    }
}

void ConsoleFrontend::display_itinerary(const Itinerary &itinerary)
{
    const auto &reservations = itinerary.getReservations();
    int count{(int)reservations.size()};
    std::cout << "Itinerary of " << count << " reservations\n";
    std::cout << itinerary.toString2() << "\n";
}

void ConsoleFrontend::read_flight_request_data(FlightRequest &request)
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

void ConsoleFrontend::read_hotel_request_data(HotelRequest &request)
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

int ConsoleFrontend::show_start_menu()
{
    std::vector<std::string> startMenu{
        "Login",
        "SignUp",
        "Exit"};

    while (true)
    {
        Printer::print_menu(startMenu);

        try
        {
            return InputHandler::get_choice(1, 3);
        }
        catch (const std::exception &e)
        {
            show_error(e.what());
        }
    }
}

void ConsoleFrontend::display_welcome_message(const std::string &firstName, const std::string &lastName)
{
    std::cout << "Welcome " << firstName << " " << lastName << "\n\n";
}

int ConsoleFrontend::display_main_menu()
{
    std::vector<std::string> startMenu{
        "View Profile",
        "Create Itinerary",
        "List My Itineraries",
        "Logout"};

    int menuCount{(int)startMenu.size()};

    while (true)
    {
        Printer::print_menu(startMenu);

        try
        {
            return InputHandler::get_choice(1, menuCount);
        }
        catch (const std::exception &e)
        {
            show_error(e.what());
        }
    }
}

void ConsoleFrontend::display_user_profile(const User &user)
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
            show_error(e.what());
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
            show_error(e.what());
        }
    }
}

void ConsoleFrontend::show_message(const std::string &msg)
{
    std::cout << msg << "\n";
}

void ConsoleFrontend::show_error(const std::string &msg)
{
    std::cout << msg << "\n";
}