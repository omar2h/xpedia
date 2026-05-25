#include "flight_itinerary_item_flow.hpp"

#include "../presenters/flight_search_presenter.hpp"
#include "application/use_cases/add_flight_to_itinerary_use_case.hpp"

FlightItineraryItemFlow::FlightItineraryItemFlow(
    FlightSearchPresenter& presenter,
    AddFlightToItineraryUseCase& addFlightUseCase)
    : m_presenter(presenter), m_addFlightUseCase(addFlightUseCase) {}

std::string FlightItineraryItemFlow::label() const
{
    return "Add Flight";
}

bool FlightItineraryItemFlow::execute(Itinerary& itinerary)
{
    auto selectedOffer = m_presenter.searchAndSelect();
    if (!selectedOffer)
        return false;
    return m_addFlightUseCase.execute(itinerary, *selectedOffer);
}
