#include "frontEnd.h"
#include "menuPrinter.h"
#include "inputHandler.h"
#include "error.h"
#include "requestDataReader.h"
#include "flightRequestDataReader.h"
#include <iostream>

RequestDataReader *FrontEnd::reader{};

int FrontEnd::show_start_menu()
{
    std::vector<std::string> startMenu{"Login", "SignUp", "Exit"};
    MenuPrinter::print(startMenu);
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
    MenuPrinter::print(startMenu);
    int choice{};
    try
    {
        choice = InputHandler::get_choice(1, 4);
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
    MenuPrinter::print(menu);
    int choice{};
    try
    {
        choice = InputHandler::get_choice(1, 4);
    }
    catch (int e)
    {
        Error::display_error(e);
        show_start_menu();
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

int FrontEnd::read_flight_choice(const std::vector<Flight> &flights)
{
}

void FrontEnd::read_request_data(ReservationRequest *req, RequestType type)
{
    if (type == RequestType::flight)
    {
        reader = new FlightRequestDataReader;
        req = reader->read();
    }
}
