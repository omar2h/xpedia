#include "app.hpp"

#include "composition/auth/auth_module.hpp"
#include "composition/flight/flight_module.hpp"
#include "composition/hotel/hotel_module.hpp"

#include "application/use_cases/add_flight_to_itinerary_use_case.hpp"
#include "application/use_cases/add_hotel_to_itinerary_use_case.hpp"
#include "application/use_cases/create_empty_itinerary_use_case.hpp"
#include "application/use_cases/list_itineraries_use_case.hpp"
#include "application/use_cases/pay_itinerary_use_case.hpp"
#include "application/services/payment_service.hpp"
#include "domain/factories/reservation_factory.hpp"
#include "infrastructure/factories/payment_factory.hpp"

#include "infrastructure/persistence/sql/sql_database.hpp"

#include "presentation/console_frontend.hpp"
#include "presentation/input.hpp"
#include "presentation/output.hpp"
#include "presentation/presenters/payment_presenter.hpp"
#include "presentation/presenters/itinerary_presenter.hpp"
#include "presentation/itinerary_item_flows/flight_itinerary_item_flow.hpp"
#include "presentation/itinerary_item_flows/hotel_itinerary_item_flow.hpp"

#include "util/env_loader.hpp"

#include <exception>
#include <iostream>
#include <memory>
#include <vector>

int main()
{
    try
    {
        loadEnvFile(".env");

        SqlDatabase database;

        ConsoleOutput output;
        ConsoleInput input;
        ConsoleFrontend view{output};

        auto authModule = createAuthModule(view, input, database);
        auto flightModule = createFlightModule(view, input);
        auto hotelModule = createHotelModule(view, input);
        ListItinerariesUseCase listItinerariesUseCase{database, database};

        ReservationFactory reservationFactory;
        PaymentFactory paymentFactory;

        CreateEmptyItineraryUseCase createItineraryUseCase;
        AddFlightToItineraryUseCase addFlightToItineraryUseCase{reservationFactory};
        AddHotelToItineraryUseCase addHotelToItineraryUseCase{reservationFactory};

        PaymentProcessor paymentProcessor{
            database,
            [&](::PaymentService service) { return paymentFactory.getPaymentService(service); },
            [](const Itinerary &) { return true; }};

        PayItineraryUseCase payItineraryUseCase{database, database, paymentProcessor};
        PaymentPresenter paymentPresenter{view, input, payItineraryUseCase};

        std::vector<std::unique_ptr<ItineraryItemFlow>> flows;
        flows.push_back(std::make_unique<FlightItineraryItemFlow>(*flightModule.presenter, addFlightToItineraryUseCase));
        flows.push_back(std::make_unique<HotelItineraryItemFlow>(*hotelModule.presenter, addHotelToItineraryUseCase));

        ItineraryPresenter itineraryPresenter{view, input, createItineraryUseCase, std::move(flows), paymentPresenter};

        App app{
            view,
            input,
            *authModule.presenter,
            itineraryPresenter,
            listItinerariesUseCase};

        app.run();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Fatal error: " << e.what() << "\n";
        return 1;
    }
}
