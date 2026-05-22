#include "composition/flight/flight_module.hpp"

#include "application/interfaces/iflight_search_service.hpp"

#include "infrastructure/config/api_config.hpp"
#include "infrastructure/flight/duffel/duffel_flight_service.hpp"

#include "presentation/console_frontend.hpp"
#include "presentation/input.hpp"

#include "util/env_loader.hpp"

FlightModule createFlightModule(ConsoleFrontend &view, ConsoleInput &input, SqlDatabase &database)
{
    (void)database;

    loadEnvFile(".env");

    std::string apiKey = ApiConfig::getEnvVar("DUFFEL_API_KEY");

    std::vector<std::unique_ptr<IFlightSearchService>> services;
    services.push_back(std::make_unique<DuffelFlightService>(apiKey));
    auto aggregatedService = std::make_unique<AggregatedFlightSearchService>(std::move(services));
    auto useCase = std::make_unique<SearchFlightsUseCase>(*aggregatedService);
    auto presenter = std::make_unique<FlightSearchPresenter>(view, input, *useCase);
    return FlightModule{std::move(aggregatedService), std::move(useCase), std::move(presenter)};
}
