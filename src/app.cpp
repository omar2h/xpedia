#include "app.hpp"
#include "frontend/console_frontend.hpp"
#include "frontend/output.hpp"
#include "frontend/input.hpp"
#include "model/user.hpp"
#include "frontend/login_handler.hpp"
#include "frontend/signup_handler.hpp"
#include "application/application.hpp"
#include "db/database.hpp"
#include "infrastructure/factories/flight_provider_factory.hpp"
#include "infrastructure/factories/hotel_provider_factory.hpp"
#include "infrastructure/factories/reservation_provider_factory.hpp"
#include "infrastructure/factories/payment_factory.hpp"
#include "model/factories/reservation_request_factory.hpp"
#include "model/factories/reservation_factory.hpp"
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
            m_frontend.showMessage("\n");
            int choice = m_frontend.showStartMenu();

            if (choice == 1)
            {
                user = m_frontend.login();
                m_frontend.displayWelcomeMessage(user.getFirstName(), user.getLastName());
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
            int choice = m_frontend.displayMainMenu();

            if (choice == 1)
            {
                m_frontend.displayUserProfile(user);
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
    RoutingReservationProviderFactory reservationProviderFactory;
    PaymentFactory paymentFactory;
    auto getFlightProviders = [&]() { return flightProviderFactory.getProviders(); };
    auto getHotelProviders = [&]() { return hotelProviderFactory.getProviders(); };
    auto getReservationProvider = [&](ReservationType type) { return reservationProviderFactory.getProvider(type); };
    auto getPaymentService = [&](PaymentService service) { return paymentFactory.getPaymentService(service); };
    ReservationRequestFactory requestFactory;
    ReservationFactory reservationFactory;
    Application application{database, getFlightProviders, getHotelProviders,
                            getReservationProvider, getPaymentService,
                            requestFactory, reservationFactory};
    ConsoleOutput output;
    ConsoleInput input;
    LoginHandler loginHandler{application, output, input};
    SignupHandler signupHandler{application, output, input};
    ConsoleFrontend frontend{application, loginHandler, signupHandler, output, input};

    App app{frontend, application};

    try
    {
        app.run();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Fatal error: " << e.what() << "\n";
    }
}