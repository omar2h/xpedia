#pragma once

#include "itinerary_item_flow.hpp"

class HotelSearchPresenter;
class AddHotelToItineraryUseCase;

class HotelItineraryItemFlow
    : public ItineraryItemFlow
{
public:
    HotelItineraryItemFlow(
        HotelSearchPresenter& presenter,
        AddHotelToItineraryUseCase& addHotelUseCase);

    std::string label() const override;

    bool execute(Itinerary& itinerary) override;

private:
    HotelSearchPresenter& m_presenter;
    AddHotelToItineraryUseCase& m_addHotelUseCase;
};
