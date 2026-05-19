#pragma once

class IView;
class IInput;
class User;
class Itinerary;
class CreateItineraryUseCase;
class PaymentPresenter;

class ItineraryPresenter
{
    IView& m_view;
    IInput& m_input;
    CreateItineraryUseCase& m_createItineraryUseCase;
    PaymentPresenter& m_paymentPresenter;

    void addFlight(Itinerary& itinerary);
    void addHotel(Itinerary& itinerary);

public:
    ItineraryPresenter(IView& view, IInput& input, CreateItineraryUseCase& useCase, PaymentPresenter& paymentPresenter);
    void run(User& user);
};
