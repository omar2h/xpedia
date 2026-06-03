#include "aggregated_hotel_search_service.hpp"

#include <iterator>
#include <string>

AggregatedHotelSearchService::AggregatedHotelSearchService(std::vector<std::unique_ptr<IHotelSearchService>> services)

    : m_services(std::move(services))
{
}

Result<std::vector<HotelOffer>> AggregatedHotelSearchService::searchHotels(const HotelSearchRequest& request)
{
    std::vector<HotelOffer> allOffers;
    std::string errors;
    bool anySucceeded = false;

    for (auto& service : m_services)
    {
        auto result = service->searchHotels(request);

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
        return Result<std::vector<HotelOffer>>::failure(errors.empty() ? "All hotel search providers failed" : errors);
    }

    return Result<std::vector<HotelOffer>>::success(std::move(allOffers));
}
