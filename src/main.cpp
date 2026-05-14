#include "app.hpp"
#include "frontend/console_frontend.hpp"
#include "frontend/output.hpp"
#include "frontend/input.hpp"
#include "frontend/login_handler.hpp"
#include "frontend/signup_handler.hpp"
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
#include "infrastructure/providers/british_airways_flight_provider.hpp"
#include "infrastructure/providers/air_france_flight_provider.hpp"
#include "infrastructure/providers/marriott_hotel_provider.hpp"
#include "infrastructure/providers/hilton_hotel_provider.hpp"
#include "infrastructure/factories/payment_factory.hpp"
#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <functional>

static void registerReservationProviders(ReservationProviderFactory &factory)
{
    factory.registerProvider(ReservationCategory::flight, "british_airways", "British Airways",
                             [] { return std::make_unique<BritishAirwaysFlightProvider>(); });
    factory.registerProvider(ReservationCategory::flight, "air_france", "Air France",
                             [] { return std::make_unique<AirFranceFlightProvider>(); });
    factory.registerProvider(ReservationCategory::hotel, "marriott", "Marriott",
                             [] { return std::make_unique<MarriottHotelProvider>(); });
    factory.registerProvider(ReservationCategory::hotel, "hilton", "Hilton",
                             [] { return std::make_unique<HiltonHotelProvider>(); });
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
    PayItineraryUseCase payItineraryUseCase{database, paymentProcessor};
    ListItinerariesUseCase listItinerariesUseCase{database};
    CreateItineraryUseCase createItineraryUseCase{requestFactory, reservationFactory, reservationService};
    ConsoleOutput output;
    ConsoleInput input;
    LoginHandler loginHandler{authService, output, input};
    SignupHandler signupHandler{authService, output, input};
    ConsoleFrontend frontend{loginHandler, signupHandler, output, input};

    App app{frontend, createItineraryUseCase, payItineraryUseCase,
            listItinerariesUseCase};

    try
    {
        app.run();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Fatal error: " << e.what() << "\n";
    }
}
