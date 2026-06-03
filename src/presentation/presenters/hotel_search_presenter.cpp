#include "hotel_search_presenter.hpp"

#include "../view/view_interface.hpp"
#include "application/dto/hotel_search_input.hpp"
#include "input.hpp"

#include "../forms/hotel_search_form.hpp"
#include "../mappers/hotel_offer_selection_mapper.hpp"
#include "../presenter_helpers.hpp"

HotelSearchPresenter::HotelSearchPresenter(IView &view, IInput &input, SearchHotelsUseCase &useCase)
    : m_view(view),
      m_input(input),
      m_useCase(useCase)
{
}

std::optional<SelectedHotelOffer> HotelSearchPresenter::searchAndSelect()
{
    auto input = HotelSearchForm::collect(m_view, m_input);

    auto result = m_useCase.execute(input);

    if (!result.isSuccess())
    {
        m_view.showError(result.error());
        return std::nullopt;
    }

    const auto &offers = result.value();
    if (offers.empty())
    {
        m_view.showMessage("No hotels found");
        return std::nullopt;
    }

    auto selectionList = HotelOfferSelectionMapper::map(offers);

    m_view.displayHotelOffers(selectionList.viewModel);

    int sel = readChoice(m_view, m_input, "Enter choice(-1 to cancel): ", 1, static_cast<int>(selectionList.viewModel.offers.size()), true);
    if (sel == -1)
        return std::nullopt;

    auto [offerIdx, roomIdx] = selectionList.selectionMap[sel - 1];
    HotelOffer selected = offers[offerIdx];
    if (roomIdx >= 0 && roomIdx < static_cast<int>(selected.roomOffers.size()))
    {
        HotelRoomOffer selectedRoom = selected.roomOffers[roomIdx];
        selected.roomOffers.clear();
        selected.roomOffers.push_back(selectedRoom);
        selected.totalPrice = selectedRoom.totalAmount;
    }
    return SelectedHotelOffer{input, selected};
}
