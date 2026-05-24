#include "composition/hotel/hotel_module.hpp"

#include "application/interfaces/ihotel_search_service.hpp"

#include "infrastructure/config/api_config.hpp"
#include "infrastructure/hotel/liteapi/liteapi_hotel_service.hpp"
#include "presentation/console_frontend.hpp"
#include "presentation/input.hpp"

#include "util/env_loader.hpp"

HotelModule createHotelModule(ConsoleFrontend &view, ConsoleInput &input, SqlDatabase &database)
{
    (void)database;

    loadEnvFile(".env");

    std::string apiKey = ApiConfig::getEnvVar("LITEAPI_KEY");

    std::vector<std::unique_ptr<IHotelSearchService>> services;
    services.push_back(std::make_unique<LiteApiHotelService>(apiKey));
    auto aggregatedService = std::make_unique<AggregatedHotelSearchService>(std::move(services));
    auto useCase = std::make_unique<SearchHotelsUseCase>(*aggregatedService);
    auto presenter = std::make_unique<HotelSearchPresenter>(view, input, *useCase);
    return HotelModule{std::move(aggregatedService), std::move(useCase), std::move(presenter)};
}
