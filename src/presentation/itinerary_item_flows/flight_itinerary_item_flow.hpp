#pragma once

#include "itinerary_item_flow.hpp"

class FlightSearchPresenter;
class AddFlightToItineraryUseCase;

class FlightItineraryItemFlow : public ItineraryItemFlow
{
  public:
    FlightItineraryItemFlow(FlightSearchPresenter& presenter, AddFlightToItineraryUseCase& addFlightUseCase);

    std::string label() const override;

    bool execute(Itinerary& itinerary) override;

  private:
    FlightSearchPresenter& m_presenter;
    AddFlightToItineraryUseCase& m_addFlightUseCase;
};
