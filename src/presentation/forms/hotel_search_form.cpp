#include "hotel_search_form.hpp"
#include "../view/view_interface.hpp"
#include "../input.hpp"

HotelSearchInput HotelSearchForm::collect(IView &view, IInput &input)
{
    HotelSearchInput result;
    view.showPrompt("Enter City: ");
    result.city = input.readLine();

    view.showPrompt("Enter Check-in Date (YYYY-MM-DD): ");
    result.fromDate = input.readLine();

    view.showPrompt("Enter Check-out Date (YYYY-MM-DD): ");
    result.toDate = input.readLine();

    view.showPrompt("Enter Adults: ");
    result.adults = input.readInt();

    view.showPrompt("Enter Children: ");
    result.children = input.readInt();

    view.showPrompt("Enter Rooms: ");
    result.rooms = input.readInt();

    return result;
}
