#include "app.hpp"
#include "frontend/frontend.hpp"
#include "frontend/console_frontend.hpp"
#include "model/user.hpp"
#include "frontend/login_handler.hpp"
#include "frontend/signup_handler.hpp"
#include "backend/backend.hpp"
#include "db/database.hpp"
#include <iostream>

[[noreturn]] void App::run()
{
    Database database;
    Backend backend{database};
    LoginHandler loginHandler{backend};
    SignupHandler signupHandler{backend};
    ConsoleFrontend frontend{backend, loginHandler, signupHandler};

    User user;
    while (true)
    {
        while (true)
        {
            std::cout << "\n\n";
            int choice = frontend.show_start_menu();

            if (choice == 1)
            {
                user = frontend.login();
                frontend.display_welcome_message(user.getFirstName(), user.getLastName());
                break;
            }
            else if (choice == 2)
            {
                frontend.signup();
            }
            else if (choice == 3)
                exit(0);
        }

        while (true)
        {
            int choice = frontend.display_main_menu();

            if (choice == 1)
            {
                frontend.display_user_profile(user);
            }
            else if (choice == 2)
            {
                backend.create_itinerary(user, frontend);
            }
            else if (choice == 3)
            {
                backend.list_itineraries(user, frontend);
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