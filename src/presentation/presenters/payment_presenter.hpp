#pragma once

class IView;
class IInput;
class User;
class Itinerary;
class PayItineraryUseCase;
class ICustomerRepository;

class PaymentPresenter
{
    IView& m_view;
    IInput& m_input;
    PayItineraryUseCase& m_payItineraryUseCase;
    ICustomerRepository& m_customerRepo;

public:
    PaymentPresenter(IView& view, IInput& input, PayItineraryUseCase& useCase, ICustomerRepository& customerRepo);
    bool run(User& user, Itinerary& itinerary);
};
