#include "hotel_search_presenter.hpp"

#include "../view/view_interface.hpp"
#include "application/dto/hotel_search_input.hpp"
#include "input.hpp"
#include "infrastructure/persistence/sql/sql_database.hpp"
#include "../forms/hotel_search_form.hpp"
#include "../mappers/hotel_offer_mapper.hpp"

#include <algorithm>

HotelSearchPresenter::HotelSearchPresenter(IView &view, IInput &input, SearchHotelsUseCase &useCase)
    : m_view(view),
      m_input(input),
      m_useCase(useCase)
{
}

void HotelSearchPresenter::run(User &user)
{
    (void)user;

    auto input = HotelSearchForm::collect(m_view, m_input);

    auto result = m_useCase.execute(input);

    if (!result.isSuccess())
    {
        m_view.showError(result.error());
        return;
    }

    HotelOfferListView viewModel;

    int index = 1;
    int hotelCount = 0;
    for (const auto &offer : result.value())
    {
        if (hotelCount > 5)
            break;
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
        }
        else
        {
            // for (const auto &room : offer.roomOffers)
            for (int i = 0; i < std::min(offer.roomOffers.size(), static_cast<size_t>(5)); i++)
            {
                auto item = HotelOfferMapper::map(
                    offer,
                    offer.roomOffers[i],
                    index++);

                if (firstRoom)
                {
                    item.hotelName = offer.accommodationName;
                    firstRoom = false;
                }

                viewModel.offers.push_back(std::move(item));
            }
        }
        hotelCount++;
    }

    m_view.displayHotelOffers(viewModel);
}