#include "app.h"
#include "frontEnd.h"
#include "user.h"
#include "signupHandler.h"
#include "loginHandler.h"
#include <iostream>

[[noreturn]] void App::run() const
{
    User user;
    while (true)
    {
        int choice = FrontEnd::show_start_menu();

        if (choice == 1)
        {
            user = LoginHandler::login();
            FrontEnd::display_welcome_message(user.getFirstName(), user.getLastName());
            break;
        }
        else if (choice == 2)
            SignupHandler::signup();
        else if (choice == 3)
            exit(0);
    }

    while (true)
    {
        int choice = FrontEnd::display_main_menu();

        if (choice == 1)
        {
            FrontEnd::display_user_profile(user);
        }
        else if (choice == 2)
        {
            // create Itinerary
            ;
        }
        else if (choice == 3)
        {
            // list itineraries
            ;
        }
        else if (choice == 4)
        {
            // logout
            ;
        }
    }
}

int main()
{
    App app;
    app.run();
}