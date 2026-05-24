#include "hotel_search_presenter.hpp"

#include "../forms/hotel_search_form.hpp"
#include "../view/view_interface.hpp"
#include "../input.hpp"
#include "domain/entities/user.hpp"

HotelSearchPresenter::HotelSearchPresenter(
    IView &view,
    IInput &input,
    SearchHotelsUseCase &useCase)

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

    for (const auto &offer : result.value())
    {
        HotelOfferViewModel item;
        item.number = index++;
        item.accommodationName = offer.accommodationName;
        item.cityName = offer.cityName;
        item.countryCode = offer.countryCode;
        item.address = offer.address;
        item.rating = offer.rating;
        item.reviewScore = offer.reviewScore;
        item.reviewCount = offer.reviewCount;
        item.checkInDate = offer.checkInDate;
        item.checkOutDate = offer.checkOutDate;
        item.rooms = offer.rooms;
        item.price = offer.cheapestRateTotalAmount;
        item.currency = offer.cheapestRateCurrency;
        item.roomOptions = static_cast<int>(offer.roomOffers.size());
        item.amenityCount = static_cast<int>(offer.amenities.size());
        item.phoneNumber = offer.phoneNumber;
        viewModel.offers.push_back(item);
    }

    m_view.displayHotelOffers(viewModel);
}
