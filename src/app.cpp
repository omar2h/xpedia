#include "app.hpp"
#include "frontend/frontend.hpp"
#include "frontend/console_frontend.hpp"
#include "model/user.hpp"
#include "frontend/login_handler.hpp"
#include "frontend/signup_handler.hpp"
#include "backend/backend.hpp"
#include "db/database.hpp"
#include <iostream>

App::App(IFrontend &frontend, Backend &backend)
    : m_frontend(frontend), m_backend(backend) {}

void App::run()
{
    User user;
    while (true)
    {
        while (true)
        {
            std::cout << "\n\n";
            int choice = m_frontend.show_start_menu();

            if (choice == 1)
            {
                user = m_frontend.login();
                m_frontend.display_welcome_message(user.getFirstName(), user.getLastName());
                break;
            }
            else if (choice == 2)
            {
                m_frontend.signup();
            }
            else if (choice == 3)
                return;
        }

        while (true)
        {
            int choice = m_frontend.display_main_menu();

            if (choice == 1)
            {
                m_frontend.display_user_profile(user);
            }
            else if (choice == 2)
            {
                m_backend.create_itinerary(user, m_frontend);
            }
            else if (choice == 3)
            {
                m_backend.list_itineraries(user, m_frontend);
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
    Database database;
    Backend backend{database};
    LoginHandler loginHandler{backend};
    SignupHandler signupHandler{backend};
    ConsoleFrontend frontend{backend, loginHandler, signupHandler};

    App app{frontend, backend};
    app.run();
}