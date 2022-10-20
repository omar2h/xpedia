#include "frontEnd.h"
#include "menuPrinter.h"
#include "inputHandler.h"
#include "error.h"
#include <vector>
#include <iostream>

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
