#include "flight_search_presenter.hpp"

#include "../forms/flight_search_form.hpp"
#include "../view/view_interface.hpp"
#include "../input.hpp"
#include "../presenter_helpers.hpp"

FlightSearchPresenter::FlightSearchPresenter(
    IView &view,
    IInput &input,
    SearchFlightsUseCase &useCase)
    : m_view(view),
      m_input(input),
      m_useCase(useCase)
{
}

std::optional<SelectedFlightOffer> FlightSearchPresenter::searchAndSelect()
{
    auto input = FlightSearchForm::collect(m_view, m_input);
    auto result = m_useCase.execute(input);

    if (!result.isSuccess())
    {
        m_view.showError(result.error());
        return std::nullopt;
    }

    const auto &offers = result.value();
    if (offers.empty())
    {
        m_view.showMessage("No flights found");
        return std::nullopt;
    }

    FlightOfferListView viewModel;
    int index = 1;

    for (const auto &offer : offers)
    {
        FlightOfferViewModel item;
        item.number = index++;
        item.price = offer.totalAmount + " " + offer.currency;
        item.duration = offer.duration;
        item.multiSegment = offer.segments.size() > 1;

        if (!offer.segments.empty())
        {
            const auto &first = offer.segments.front();
            const auto &last = offer.segments.back();
            item.airline = first.airline.name;
            item.flightNumber = first.flightNumber;
            item.route = first.fromIata + " -> " + last.toIata;
            item.departureTime = first.departureTime;
            item.arrivalTime = last.arrivalTime;
            item.aircraft = first.aircraft;
            item.cabin = first.cabinClass;
            item.baggage = std::to_string(first.checkedBagQuantity) + " bag(s)";
            item.stops = std::to_string(static_cast<int>(offer.segments.size()) - 1);
        }
        viewModel.offers.push_back(item);
    }

    m_view.displayFlightOffers(viewModel);

    int sel = readChoice(m_view, m_input, "Enter choice(-1 to cancel): ", 1, static_cast<int>(offers.size()), true);
    if (sel == -1)
        return std::nullopt;

    return SelectedFlightOffer{input, offers[sel - 1]};
}
