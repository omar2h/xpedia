#include "aggregated_flight_search_service.hpp"

#include <iterator>
#include <string>

AggregatedFlightSearchService::AggregatedFlightSearchService(
    std::vector<std::unique_ptr<IFlightSearchService>> services)

    : m_services(std::move(services))
{
}

Result<std::vector<FlightOffer>> AggregatedFlightSearchService::searchFlights(const FlightSearchRequest& request)
{
    std::vector<FlightOffer> allOffers;
    std::string errors;
    bool anySucceeded = false;

    for (auto& service : m_services)
    {
        auto result = service->searchFlights(request);

        if (!result.isSuccess())
        {
            if (!errors.empty())
            {
                errors += "; ";
            }
            errors += result.error();
            continue;
        }

        anySucceeded = true;
        auto& offers = result.value();

        allOffers.insert(allOffers.end(), std::make_move_iterator(offers.begin()),
                         std::make_move_iterator(offers.end()));
    }

    if (!anySucceeded)
    {
        return Result<std::vector<FlightOffer>>::failure(errors.empty() ? "All flight search providers failed"
                                                                        : errors);
    }

    return Result<std::vector<FlightOffer>>::success(std::move(allOffers));
}