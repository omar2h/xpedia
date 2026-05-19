#include "itinerary_presenter.hpp"
#include "payment_presenter.hpp"
#include "../view/view_interface.hpp"
#include "../input.hpp"
#include "../app_state.hpp"
#include "../presenter_helpers.hpp"
#include "../forms/flight_search_form.hpp"
#include "../forms/hotel_search_form.hpp"
#include "../mappers/search_result_mapper.hpp"
#include "../mappers/itinerary_mapper.hpp"
#include "../../domain/entities/itinerary.hpp"
#include "../../application/use_cases/create_itinerary_use_case.hpp"
#include "../../exception.hpp"

ItineraryPresenter::ItineraryPresenter(IView& view, IInput& input, CreateItineraryUseCase& useCase, PaymentPresenter& paymentPresenter)
    : m_view(view), m_input(input), m_createItineraryUseCase(useCase), m_paymentPresenter(paymentPresenter) {}

void ItineraryPresenter::run(User& user)
{
    Itinerary itinerary = m_createItineraryUseCase.createItinerary();

    while (true)
    {
        m_view.showCreateItineraryMenu();
        int choice = readChoice(m_view, m_input, "", 1, 4);

        switch (static_cast<CreateItineraryMenuChoice>(choice))
        {
        case CreateItineraryMenuChoice::AddFlight:
            addFlight(itinerary);
            break;
        case CreateItineraryMenuChoice::AddHotel:
            addHotel(itinerary);
            break;
        case CreateItineraryMenuChoice::CheckOut:
        {
            if (itinerary.getReservations().empty())
            {
                m_view.showMessage("Cannot checkout: itinerary is empty");
                break;
            }
            m_view.displayItinerary(toItineraryViewModel(itinerary));
            m_paymentPresenter.run(user, itinerary);
            return;
        }
        case CreateItineraryMenuChoice::Cancel:
            return;
        default:
            m_view.showError("Invalid choice");
            break;
        }
    }
}

void ItineraryPresenter::addFlight(Itinerary& itinerary)
{
    auto input = FlightSearchForm::collect(m_view, m_input);
    auto items = m_createItineraryUseCase.searchFlights(input);

    if (items.empty())
    {
        m_view.showMessage("No flights found");
        return;
    }

    std::vector<SearchResultViewModel> viewModels;
    for (const auto& item : items)
        viewModels.push_back(toSearchResultViewModel(*item));

    m_view.showSearchResults(viewModels);
    int sel = readChoice(m_view, m_input, "Enter choice(-1 to cancel): ", 1, static_cast<int>(items.size()), true);

    if (sel != -1 &&
        !m_createItineraryUseCase.addFlightToItinerary(itinerary, input, *items[sel - 1]))
    {
        m_view.showError("Failed to add flight to itinerary");
    }
}

void ItineraryPresenter::addHotel(Itinerary& itinerary)
{
    auto input = HotelSearchForm::collect(m_view, m_input);
    auto items = m_createItineraryUseCase.searchHotels(input);

    if (items.empty())
    {
        m_view.showMessage("No hotels found");
        return;
    }

    std::vector<SearchResultViewModel> viewModels;
    for (const auto& item : items)
        viewModels.push_back(toSearchResultViewModel(*item));

    m_view.showSearchResults(viewModels);
    int sel = readChoice(m_view, m_input, "Enter choice(-1 to cancel): ", 1, static_cast<int>(items.size()), true);

    if (sel != -1 &&
        !m_createItineraryUseCase.addHotelToItinerary(itinerary, input, *items[sel - 1]))
    {
        m_view.showError("Failed to add hotel to itinerary");
    }
}
