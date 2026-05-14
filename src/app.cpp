#include "app.hpp"
#include "frontend/console_frontend.hpp"
#include "frontend/output.hpp"
#include "frontend/input.hpp"
#include "domain/entities/user.hpp"
#include "domain/entities/payment_card.hpp"
#include "domain/entities/itinerary.hpp"
#include "domain/entities/itinerary_item.hpp"
#include "application/factories/reservation_request_factory.hpp"
#include "domain/factories/reservation_factory.hpp"
#include "frontend/login_handler.hpp"
#include "frontend/signup_handler.hpp"
#include "application/services/auth_service.hpp"
#include "application/services/reservation_service.hpp"
#include "application/services/payment_service.hpp"
#include "application/use_cases/create_itinerary_use_case.hpp"
#include "application/use_cases/pay_itinerary_use_case.hpp"
#include "application/use_cases/list_itineraries_use_case.hpp"
#include "application/results/pay_itinerary_result.hpp"
#include "application/results/list_itineraries_result.hpp"
#include "infrastructure/persistence/sql/sql_database.hpp"
#include "infrastructure/factories/reservation_provider_factory.hpp"
#include "infrastructure/providers/british_airways_flight_provider.hpp"
#include "infrastructure/providers/air_france_flight_provider.hpp"
#include "infrastructure/providers/marriott_hotel_provider.hpp"
#include "infrastructure/providers/hilton_hotel_provider.hpp"
#include "infrastructure/factories/payment_factory.hpp"
#include <iostream>

App::App(IFrontend &frontend,
         CreateItineraryUseCase &createItineraryUseCase,
         PayItineraryUseCase &payItineraryUseCase,
         ListItinerariesUseCase &listItinerariesUseCase,
         ReservationRequestFactory &requestFactory)
    : m_frontend(frontend),
      m_createItineraryUseCase(createItineraryUseCase),
      m_payItineraryUseCase(payItineraryUseCase),
      m_listItinerariesUseCase(listItinerariesUseCase),
      m_requestFactory(requestFactory) {}

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
                handleCreateItinerary(user);
            }
            else if (choice == 3)
            {
                auto result = m_listItinerariesUseCase.execute(user);
                if (result.success)
                    m_frontend.displayItineraries(result.itineraries);
                else
                    m_frontend.showMessage(result.message);
            }
            else if (choice == 4)
            {
                break;
            }
        }
    }
}

void App::handleCreateItinerary(User &user)
{
    Itinerary itinerary = m_createItineraryUseCase.createItinerary();

    while (true)
    {
        int choice = m_frontend.displayCreateItineraryMenu();

        if (choice == 1)
        {
            addItemToItinerary(itinerary, RequestType::flight);
        }
        else if (choice == 2)
        {
            addItemToItinerary(itinerary, RequestType::hotel);
        }
        else if (choice == 3)
        {
            m_frontend.displayItinerary(itinerary);
            handlePayment(user, itinerary);
            return;
        }
        else if (choice == 4)
        {
            return;
        }
    }
}

void App::addItemToItinerary(Itinerary &itinerary, RequestType type)
{
    auto request = m_requestFactory.getRequest(type);
    m_frontend.readRequestData(*request, type);

    auto items = m_createItineraryUseCase.searchItems(type, *request);
    int sel = m_frontend.readReservationChoice(items);

    if (sel != -1)
        m_createItineraryUseCase.addItemToItinerary(itinerary, type, std::move(request), *items[sel - 1]);
}

bool App::handlePayment(User &user, const Itinerary &itinerary)
{
    auto cards = m_payItineraryUseCase.getCustomerCards(user);

    while (true)
    {
        int choice = m_frontend.displayPaymentOptions(cards);

        if (choice == -1)
            return false;

        if (choice == 0)
        {
            PaymentCard newCard = m_frontend.readCard();
            m_payItineraryUseCase.addCard(user, newCard);
            cards = m_payItineraryUseCase.getCustomerCards(user);
            continue;
        }

        PaymentCard selectedCard = cards[choice - 1];

        int serviceChoice = m_frontend.displayPaymentServices();
        if (serviceChoice == -1)
            return false;

        auto result = m_payItineraryUseCase.execute(user, itinerary, selectedCard, serviceChoice);

        if (result.status == PayItineraryResult::Confirmed)
        {
            m_frontend.showMessage(result.message);
            return true;
        }

        m_frontend.showError(result.message);
        return false;
    }
}

int main()
{
    SqlDatabase database;
    ReservationProviderFactory providerFactory;
    providerFactory.registerProvider(ReservationCategory::flight, "british_airways", "British Airways",
                                     [] { return std::make_unique<BritishAirwaysFlightProvider>(); });
    providerFactory.registerProvider(ReservationCategory::flight, "air_france", "Air France",
                                     [] { return std::make_unique<AirFranceFlightProvider>(); });
    providerFactory.registerProvider(ReservationCategory::hotel, "marriott", "Marriott",
                                     [] { return std::make_unique<MarriottHotelProvider>(); });
    providerFactory.registerProvider(ReservationCategory::hotel, "hilton", "Hilton",
                                     [] { return std::make_unique<HiltonHotelProvider>(); });
    PaymentFactory paymentFactory;
    auto getProviders = [&](ReservationCategory category)
    { return providerFactory.createAll(category); };
    auto getReservationProvider = [&](ReservationCategory category, const std::string &providerId)
    { return providerFactory.create(category, providerId); };
    auto getPaymentService = [&](PaymentService service)
    { return paymentFactory.getPaymentService(service); };
    ReservationRequestFactory requestFactory;
    ReservationFactory reservationFactory;
    AuthService authService{database};
    ReservationService reservationService{getProviders, getReservationProvider};
    auto confirmReservations = [&](const Itinerary &itin)
    { return reservationService.confirmReservations(itin); };
    PaymentProcessor paymentProcessor{database, getPaymentService, confirmReservations};
    PayItineraryUseCase payItineraryUseCase{database, paymentProcessor};
    ListItinerariesUseCase listItinerariesUseCase{database};
    CreateItineraryUseCase createItineraryUseCase{requestFactory, reservationFactory, reservationService};
    ConsoleOutput output;
    ConsoleInput input;
    LoginHandler loginHandler{authService, output, input};
    SignupHandler signupHandler{authService, output, input};
    ConsoleFrontend frontend{loginHandler, signupHandler, output, input};

    App app{frontend, createItineraryUseCase, payItineraryUseCase,
            listItinerariesUseCase, requestFactory};

    try
    {
        app.run();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Fatal error: " << e.what() << "\n";
    }
}
