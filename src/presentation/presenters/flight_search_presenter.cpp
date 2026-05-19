#include "flight_search_presenter.hpp"
#include "../forms/flight_search_form.hpp"
#include "../../application/interfaces/iflight_search_service.hpp"
#include "../view/view_interface.hpp"
#include "../input.hpp"
#include "../view_models/view_models.hpp"
#include "../../domain/entities/user.hpp"
#include "../../domain/entities/flight.hpp"
#include "../../domain/entities/flight_reservation.hpp"
#include "../../domain/entities/itinerary.hpp"
#include "../../domain/value_objects/flight_search_request.hpp"
#include "../../domain/value_objects/flight_offer.hpp"
#include "../../domain/entities/reservation_category.hpp"
#include "../../domain/request_type.hpp"
#include "../../application/interfaces/iflight_search_service.hpp"
#include "../../application/repositories/i_itinerary_repository.hpp"
#include "../../util/id_generator.hpp"
#include <memory>
#include <algorithm>
#include <cctype>
#include <unordered_set>

namespace
{

    std::string capitalize(std::string text)
    {
        if (!text.empty())
        {
            text[0] = static_cast<char>(
                std::toupper(text[0]));
        }

        return text;
    }

    std::string buildRoute(
        const std::vector<FlightSegment> &segments)
    {
        if (segments.empty())
            return {};

        std::string route =
            segments.front().from;

        for (const auto &seg : segments)
        {
            route += " -> " + seg.to;
        }

        return route;
    }

    std::string buildStopsText(
        std::size_t segmentCount)
    {
        if (segmentCount <= 1)
            return "Direct";

        std::size_t stops =
            segmentCount - 1;

        return std::to_string(stops) +
               (stops == 1
                    ? " stop"
                    : " stops");
    }

} // namespace

FlightSearchPresenter::FlightSearchPresenter(
    IView &view,
    IInput &input,
    IFlightSearchService &flightSearchService,
    IItineraryRepository &itineraryRepo)
    : m_view(view),
      m_input(input),
      m_flightSearchService(flightSearchService),
      m_itineraryRepo(itineraryRepo)
{
}

void FlightSearchPresenter::run(User &user)
{
    auto input = FlightSearchForm::collect(m_view, m_input);

    FlightSearchRequest request;

    request.origin =
        input.origin;

    request.destination =
        input.destination;

    request.departureDate =
        input.departureDate;

    request.adults =
        input.adults;

    std::transform(
        request.origin.begin(),
        request.origin.end(),
        request.origin.begin(),
        ::toupper);

    std::transform(
        request.destination.begin(),
        request.destination.end(),
        request.destination.begin(),
        ::toupper);

    auto result =
        m_flightSearchService.searchFlights(
            request);

    if (!result.isSuccess())
    {
        m_view.showError(
            "Search failed: " +
            result.error());

        return;
    }

    auto offers = result.value();

    if (offers.empty())
    {
        m_view.showMessage(
            "No flight offers found.");

        return;
    }

    std::sort(
        offers.begin(),
        offers.end(),
        [](const FlightOffer &a,
           const FlightOffer &b)
        {
            return std::stod(a.totalAmount) < std::stod(b.totalAmount);
        });

    FlightOfferListView listView;

    std::unordered_set<std::string> seen;

    int index = 1;

    for (const auto &offer : offers)
    {
        if (offer.segments.empty())
            continue;

        const auto &first =
            offer.segments.front();

        const auto &last =
            offer.segments.back();

        FlightOfferViewModel vm;

        vm.airline =
            first.airline.name.empty()
                ? "Unknown Airline"
                : first.airline.name;

        vm.flightNumber =
            first.flightNumber;

        vm.route =
            buildRoute(offer.segments);

        vm.departureTime =
            first.departureTime;

        vm.arrivalTime =
            last.arrivalTime;

        vm.duration =
            offer.duration;

        vm.cabin =
            capitalize(
                first.cabinClass.empty()
                    ? "Economy"
                    : first.cabinClass);

        vm.aircraft =
            first.aircraft;

        vm.stops =
            buildStopsText(
                offer.segments.size());

        if (first.checkedBags > 0)
        {
            vm.baggage =
                std::to_string(
                    first.checkedBags) +
                " checked bag";

            if (first.checkedBags > 1)
                vm.baggage += "s";
        }

        vm.price =
            offer.currency +
            " " +
            offer.totalAmount;

        vm.multiSegment =
            offer.segments.size() > 1;

        std::string dedupeKey =
            vm.airline + "|" +
            vm.route + "|" +
            vm.price;

        if (seen.count(dedupeKey))
            continue;

        seen.insert(dedupeKey);

        vm.number = index++;

        listView.offers.push_back(
            std::move(vm));

        if (listView.offers.size() >= 10)
            break;
    }

    m_view.displayFlightOffers(listView);
}
