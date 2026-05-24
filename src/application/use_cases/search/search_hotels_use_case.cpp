#include "search_hotels_use_case.hpp"

SearchHotelsUseCase::SearchHotelsUseCase(IHotelSearchService &hotelService)
    : m_hotelService(hotelService)
{
}

Result<std::vector<HotelOffer>> SearchHotelsUseCase::execute(const HotelSearchInput &input)
{
    HotelSearchRequest request;

    request.city = input.city;
    request.latitude = input.latitude;
    request.longitude = input.longitude;
    request.checkInDate = input.fromDate;
    request.checkOutDate = input.toDate;
    request.adults = input.adults;
    request.childAges.resize(input.children);
    request.rooms = input.rooms;

    return m_hotelService.searchHotels(request);
}
