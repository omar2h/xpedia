#include "frontEnd.h"
#include "printer.h"
#include "inputHandler.h"
#include "error.h"
#include "requestDataReader.h"
#include "flightRequestDataReader.h"
#include <iostream>

RequestDataReader *FrontEnd::reader{};

int FrontEnd::show_start_menu()
{
    std::vector<std::string> startMenu{"Login", "SignUp", "Exit"};
    Printer::print_menu(startMenu);
    int choice{};
    try
    {
        choice = InputHandler::get_choice(1, 3);
    }
    catch (int e)
    {
        Error::display_error(e);
        show_start_menu();
    }
    return choice;
}

void FrontEnd::display_welcome_message(const std::string &firstName, const std::string &lastName)
{
    std::cout << "Welcome " << firstName << " " << lastName << "\n\n";
}

int FrontEnd::display_main_menu()
{
    std::vector<std::string> startMenu{"View Profile", "Create Itinerary", "List My Itineraries", "Logout"};
    Printer::print_menu(startMenu);
    int menuCount{(int)startMenu.size()};
    int choice{};
    try
    {
        choice = InputHandler::get_choice(1, menuCount);
    }
    catch (int e)
    {
        Error::display_error(e);
        show_start_menu();
    }
    return choice;
}

void FrontEnd::display_user_profile(const User &user)
{
    std::cout << "\n";
    std::cout << "Name: " << user.getFirstName() << " " << user.getLastName() << "\n";
    std::cout << "Email: " << user.getEmail() << "\n";
    std::cout << "Phone: " << user.getPhone() << "\n";
    std::cout << "\n";
}

int FrontEnd::display_create_itinerary_menu()
{
    std::vector<std::string> menu{"Add Flight", "Add Hotel", "Check Out", "Cancel"};
    Printer::print_menu(menu);
    int menuCount{(int)menu.size()};
    int choice{};
    try
    {
        choice = InputHandler::get_choice(1, menuCount);
    }
    catch (int e)
    {
        Error::display_error(e);
        display_create_itinerary_menu();
    }
    return choice;
}

int FrontEnd::display_payment_options(const std::vector<PaymentCard> &cards)
{
    Printer::print_options(cards);
    int cardsCount{(int)cards.size()};
    int choice{};
    try
    {
        choice = InputHandler::get_choice(0, cardsCount);
    }
    catch (int e)
    {
        Error::display_error(e);
        display_payment_options(cards);
    }
    return choice;
}

void FrontEnd::read_flight_request_data(FlightRequest &request)
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
    std::cout << "Enter date: ";
    std::cin >> date;
    std::cout << "Enter number of adults and children: ";
    std::cin >> adults >> children;

    request.setFromCity(from);
    request.setToCity(to);
    request.setDate(date);
    request.setAdults(adults);
    request.setChildren(children);
}

int FrontEnd::read_reservation_choice(const std::vector<ItineraryItem *> &items)
{
    Printer::print_available_itinerary_items(items);
    int itemsCount{(int)items.size()};

    int choice{};
    try
    {
        choice = InputHandler::get_choice(1, itemsCount);
    }
    catch (int e)
    {
        Error::display_error(e);
        read_reservation_choice(items);
    }
    return choice;
}

void FrontEnd::read_request_data(ReservationRequest *&req, RequestType type)
{
    if (type == RequestType::flight)
    {
        reader = new FlightRequestDataReader;
        req = reader->read();
    }
}

PaymentCard FrontEnd::read_card()
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
