#pragma once

#include "presentation/app_state.hpp"

class IView;
class IInput;
class User;
class AuthPresenter;
class ItineraryPresenter;
class ListItinerariesUseCase;

class App
{
    IView &m_view;
    IInput &m_input;
    AuthPresenter &m_authPresenter;
    ItineraryPresenter &m_itineraryPresenter;
    ListItinerariesUseCase &m_listItinerariesUseCase;

    AppState handleMainMenu(User &currentUser);

public:
    App(IView &view, IInput &input,
        AuthPresenter &authPresenter,
        ItineraryPresenter &itineraryPresenter,
        ListItinerariesUseCase &listItinerariesUseCase);
    void run();
};
