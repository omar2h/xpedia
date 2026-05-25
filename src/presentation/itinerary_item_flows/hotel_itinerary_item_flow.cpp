#include "hotel_itinerary_item_flow.hpp"

#include "../presenters/hotel_search_presenter.hpp"
#include "application/use_cases/add_hotel_to_itinerary_use_case.hpp"

HotelItineraryItemFlow::HotelItineraryItemFlow(
    HotelSearchPresenter& presenter,
    AddHotelToItineraryUseCase& addHotelUseCase)
    : m_presenter(presenter), m_addHotelUseCase(addHotelUseCase) {}

std::string HotelItineraryItemFlow::label() const
{
    return "Add Hotel";
}

bool HotelItineraryItemFlow::execute(Itinerary& itinerary)
{
    auto selectedOffer = m_presenter.searchAndSelect();
    if (!selectedOffer)
        return false;
    return m_addHotelUseCase.execute(itinerary, *selectedOffer);
}
