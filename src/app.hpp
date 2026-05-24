#pragma once

#include "presentation/app_state.hpp"

class IView;
class IInput;
class User;
class AuthPresenter;
class FlightSearchPresenter;
class HotelSearchPresenter;
class ListItinerariesUseCase;

class App
{
    IView &m_view;
    IInput &m_input;
    AuthPresenter &m_authPresenter;
    FlightSearchPresenter &m_flightSearchPresenter;
    HotelSearchPresenter &m_hotelSearchPresenter;
    ListItinerariesUseCase &m_listItinerariesUseCase;

    AppState handleMainMenu(User &currentUser);

public:
    App(IView &view, IInput &input,
        AuthPresenter &authPresenter,
        FlightSearchPresenter &flightSearchPresenter,
        HotelSearchPresenter &hotelSearchPresenter,
        ListItinerariesUseCase &listItinerariesUseCase);
    void run();
};
