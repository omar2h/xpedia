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
            int choice = Frontend::show_start_menu();

            if (choice == 1)
            {

                user = Frontend::login();
                Frontend::display_welcome_message(user.getFirstName(), user.getLastName());
                break;
            }
            else if (choice == 2)
            {
                Frontend::signup();
            }
            else if (choice == 3)
                exit(0);
        }

        // main menu loop
        while (true)
        {
            int choice = Frontend::display_main_menu();

            if (choice == 1)
            {
                Frontend::display_user_profile(user);
            }
            else if (choice == 2)
            {
                Backend::create_itinerary(user);
            }
            else if (choice == 3)
            {
                Backend::list_itineraries(user);
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