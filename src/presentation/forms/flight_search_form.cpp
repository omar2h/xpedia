#include "flight_search_form.hpp"
#include "../view/view_interface.hpp"
#include "../input.hpp"

FlightSearchInput FlightSearchForm::collect(
    IView &view,
    IInput &input)
{
    FlightSearchInput result;

    view.showPrompt(
        "Origin (IATA code): ");

    result.origin =
        input.readString();

    view.showPrompt(
        "Destination (IATA code): ");

    result.destination =
        input.readString();

    view.showPrompt(
        "Departure date (YYYY-MM-DD): ");

    result.departureDate =
        input.readString();

    view.showPrompt(
        "Adults: ");

    result.adults =
        input.readInt();

    return result;
}
