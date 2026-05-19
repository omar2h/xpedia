#pragma once

class IView;
class IInput;
class User;
class Itinerary;
class PayItineraryUseCase;

class PaymentPresenter
{
    IView& m_view;
    IInput& m_input;
    PayItineraryUseCase& m_payItineraryUseCase;

public:
    PaymentPresenter(IView& view, IInput& input, PayItineraryUseCase& useCase);
    bool run(User& user, const Itinerary& itinerary);
};
