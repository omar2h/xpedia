#pragma once

#include <memory>
#include <vector>

class IView;
class IInput;
class User;
class Itinerary;
class PaymentPresenter;
class ItineraryItemFlow;
class CreateEmptyItineraryUseCase;

class ItineraryPresenter
{
    IView& m_view;
    IInput& m_input;
    CreateEmptyItineraryUseCase& m_createItineraryUseCase;
    PaymentPresenter& m_paymentPresenter;
    std::vector<std::unique_ptr<ItineraryItemFlow>> m_itemFlows;

  public:
    ItineraryPresenter(IView& view, IInput& input, CreateEmptyItineraryUseCase& createItineraryUseCase,
                       std::vector<std::unique_ptr<ItineraryItemFlow>> itemFlows, PaymentPresenter& paymentPresenter);
    void run(User& user);
};
