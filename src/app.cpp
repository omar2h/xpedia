#include "app.hpp"
#include "frontend/frontend.hpp"
#include "model/user.hpp"
#include "frontend/login_handler.hpp"
#include "frontend/signup_handler.hpp"
#include "backend/backend.hpp"
#include "error.hpp"
#include <iostream>

[[noreturn]] void App::run() const
{
    User user;
    // main loop
    while (true)
    {
        // start menu loop
        while (true)
        {
            std::cout << "\n\n";
            int choice = FrontEnd::show_start_menu();

            if (choice == 1)
            {

                user = FrontEnd::login();
                FrontEnd::display_welcome_message(user.getFirstName(), user.getLastName());
                break;
            }
            else if (choice == 2)
            {
                FrontEnd::signup();
            }
            else if (choice == 3)
                exit(0);
        }

        // main menu loop
        while (true)
        {
            int choice = FrontEnd::display_main_menu();

            if (choice == 1)
            {
                FrontEnd::display_user_profile(user);
            }
            else if (choice == 2)
            {
                BackEnd::create_itinerary(user);
            }
            else if (choice == 3)
            {
                BackEnd::list_itineraries(user);
            }
            else if (choice == 4)
            {
                break;
            }
        }
    }
}

int main()
{
    App app;
    app.run();
}