#pragma once

#include "../../domain/result.hpp"
#include "../results/pay_itinerary_result.hpp"
#include <vector>

class User;
class Customer;
class Itinerary;
class PaymentCard;
class ICustomerRepository;
class IItineraryRepository;
class PaymentProcessor;

class PayItineraryUseCase
{
    ICustomerRepository& m_customerRepo;
    IItineraryRepository& m_itineraryRepo;
    PaymentProcessor& m_paymentProcessor;

  public:
    PayItineraryUseCase(ICustomerRepository& customerRepo, IItineraryRepository& itineraryRepo,
                        PaymentProcessor& paymentProcessor);

    [[nodiscard]] std::vector<PaymentCard> getCustomerCards(const User& user);
    void addCard(const User& user, const PaymentCard& card);

    [[nodiscard]] Result<Itinerary> execute(Customer& customer, Itinerary& itinerary, int serviceChoice);
};
