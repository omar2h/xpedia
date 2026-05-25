#include "hotel_search_presenter.hpp"

#include "../view/view_interface.hpp"
#include "application/dto/hotel_search_input.hpp"
#include "input.hpp"

#include "../forms/hotel_search_form.hpp"
#include "../mappers/hotel_offer_mapper.hpp"
#include "../presenter_helpers.hpp"

#include <algorithm>
#include <vector>

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

    HotelOfferListView viewModel;
    std::vector<std::pair<int, int>> selectionMap;

    int index = 1;
    int hotelCount = 0;
    for (int oi = 0; oi < static_cast<int>(offers.size()) && hotelCount < 5; oi++)
    {
        const auto &offer = offers[oi];
        hotelCount++;
        bool firstRoom = true;

        if (offer.roomOffers.empty())
        {
            HotelRoomOffer room;

            room.totalAmount = offer.totalPrice;
            room.totalCurrency = offer.currency;

            auto item = HotelOfferMapper::map(
                offer,
                room,
                index++);

            item.hotelName = offer.accommodationName;
            viewModel.offers.push_back(std::move(item));
            selectionMap.push_back({oi, -1});
        }
        else
        {
            int maxRooms = std::min(static_cast<int>(offer.roomOffers.size()), 5);
            for (int ri = 0; ri < maxRooms; ri++)
            {
                auto item = HotelOfferMapper::map(
                    offer,
                    offer.roomOffers[ri],
                    index++);

                if (firstRoom)
                {
                    item.hotelName = offer.accommodationName;
                    firstRoom = false;
                }

                viewModel.offers.push_back(std::move(item));
                selectionMap.push_back({oi, ri});
            }
        }
    }

    m_view.displayHotelOffers(viewModel);

    int sel = readChoice(m_view, m_input, "Enter choice(-1 to cancel): ", 1, static_cast<int>(viewModel.offers.size()), true);
    if (sel == -1)
        return std::nullopt;

    auto [offerIdx, roomIdx] = selectionMap[sel - 1];
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
