#pragma once

class IView;
class IInput;
class User;
class IFlightSearchService;
class IItineraryRepository;

class FlightSearchPresenter
{
    IView& m_view;
    IInput& m_input;
    IFlightSearchService& m_flightSearchService;
    IItineraryRepository& m_itineraryRepo;

public:
    FlightSearchPresenter(IView& view, IInput& input,
                          IFlightSearchService& flightSearchService,
                          IItineraryRepository& itineraryRepo);

    void run(User& user);
};
