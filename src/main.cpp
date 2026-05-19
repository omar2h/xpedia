#include "app.hpp"
#include "presentation/console_frontend.hpp"
#include "presentation/output.hpp"
#include "presentation/input.hpp"
#include "presentation/login_handler.hpp"
#include "presentation/signup_handler.hpp"
#include "presentation/presenters/auth_presenter.hpp"
#include "presentation/presenters/itinerary_presenter.hpp"
#include "presentation/presenters/payment_presenter.hpp"
#include "presentation/presenters/flight_search_presenter.hpp"
#include "domain/entities/user.hpp"
#include "domain/entities/itinerary.hpp"
#include "domain/entities/reservation_category.hpp"
#include "application/factories/reservation_request_factory.hpp"
#include "domain/factories/reservation_factory.hpp"
#include "application/services/auth_service.hpp"
#include "application/services/reservation_service.hpp"
#include "application/services/payment_service.hpp"
#include "application/use_cases/create_itinerary_use_case.hpp"
#include "application/use_cases/pay_itinerary_use_case.hpp"
#include "application/use_cases/list_itineraries_use_case.hpp"
#include "infrastructure/persistence/sql/sql_database.hpp"
#include "infrastructure/factories/reservation_provider_factory.hpp"
#include "infrastructure/providers/marriott_hotel_provider.hpp"
#include "infrastructure/providers/hilton_hotel_provider.hpp"
#include "infrastructure/factories/payment_factory.hpp"
#include "infrastructure/config/api_config.hpp"
#include "infrastructure/apis/duffel/duffel_flight_service.hpp"
#include "util/env_loader.hpp"
#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <functional>

static void registerReservationProviders(ReservationProviderFactory &factory)
{
    factory.registerProvider(ReservationCategory::hotel, "marriott", "Marriott",
                              []
                              { return std::make_unique<MarriottHotelProvider>(); });
    factory.registerProvider(ReservationCategory::hotel, "hilton", "Hilton",
                              []
                              { return std::make_unique<HiltonHotelProvider>(); });
}

int main()
{
    SqlDatabase database;
    ReservationProviderFactory providerFactory;
    registerReservationProviders(providerFactory);
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
    PayItineraryUseCase payItineraryUseCase{database, database, paymentProcessor};
    ListItinerariesUseCase listItinerariesUseCase{database, database};
    CreateItineraryUseCase createItineraryUseCase{requestFactory, reservationFactory, reservationService};
    ConsoleOutput output;
    ConsoleInput input;
    LoginHandler loginHandler{authService, output, input};
    SignupHandler signupHandler{authService, output, input};
    ConsoleFrontend view{output};

    PaymentPresenter paymentPresenter{view, input, payItineraryUseCase};
    ItineraryPresenter itineraryPresenter{view, input, createItineraryUseCase, paymentPresenter};
    AuthPresenter authPresenter{view, input, loginHandler, signupHandler};

    loadEnvFile(".env");

    std::string apiKey = ApiConfig::getEnvVar("DUFFEL_API_KEY");
    if (apiKey.empty())
    {
        std::cerr << "Warning: DUFFEL_API_KEY not set. Flight search will fail.\n";
    }
    else
    {
        std::string masked = apiKey.size() > 8
            ? apiKey.substr(0, 4) + "****" + apiKey.substr(apiKey.size() - 4)
            : "****";
        std::cerr << "DUFFEL_API_KEY: " << masked << " (" << apiKey.size() << " chars)\n";
    }
    DuffelFlightService duffelService{apiKey};

    FlightSearchPresenter flightSearchPresenter{view, input, duffelService, database};

    App app{view, input, authPresenter, itineraryPresenter, paymentPresenter,
            flightSearchPresenter, listItinerariesUseCase};

    try
    {
        app.run();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Fatal error: " << e.what() << "\n";
    }
}
