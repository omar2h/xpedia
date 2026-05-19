#pragma once

#include "presentation/app_state.hpp"

class IView;
class IInput;
class User;
class AuthPresenter;
class ItineraryPresenter;
class PaymentPresenter;
class FlightSearchPresenter;
class ListItinerariesUseCase;

class App
{
    IView& m_view;
    IInput& m_input;
    AuthPresenter& m_authPresenter;
    ItineraryPresenter& m_itineraryPresenter;
    PaymentPresenter& m_paymentPresenter;
    FlightSearchPresenter& m_flightSearchPresenter;
    ListItinerariesUseCase& m_listItinerariesUseCase;

    AppState handleMainMenu(User& currentUser);

public:
    App(IView& view, IInput& input,
        AuthPresenter& authPresenter,
        ItineraryPresenter& itineraryPresenter,
        PaymentPresenter& paymentPresenter,
        FlightSearchPresenter& flightSearchPresenter,
        ListItinerariesUseCase& listItinerariesUseCase);
    void run();
};
