#include "app.hpp"
#include "frontend/console_frontend.hpp"
#include "model/user.hpp"
#include "frontend/login_handler.hpp"
#include "frontend/signup_handler.hpp"
#include "application/application.hpp"
#include "db/database.hpp"
#include "infrastructure/factories/flight_provider_factory.hpp"
#include "infrastructure/factories/hotel_provider_factory.hpp"
#include "infrastructure/factories/reservation_provider_factory.hpp"
#include <iostream>

App::App(IFrontend &frontend, Application &backend)
    : m_frontend(frontend), m_application(backend) {}

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
                m_application.createItinerary(user, m_frontend);
            }
            else if (choice == 3)
            {
                m_application.listItineraries(user, m_frontend);
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
    FlightProviderFactory flightProviderFactory;
    HotelProviderFactory hotelProviderFactory;
    ReservationProviderFactory reservationProviderFactory;
    Application application{database, flightProviderFactory, hotelProviderFactory, reservationProviderFactory};
    LoginHandler loginHandler{application};
    SignupHandler signupHandler{application};
    ConsoleFrontend frontend{application, loginHandler, signupHandler};

    App app{frontend, application};
    app.run();
}