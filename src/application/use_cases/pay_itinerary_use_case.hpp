#pragma once

#include <vector>
#include "../results/pay_itinerary_result.hpp"

class User;
class Itinerary;
class PaymentCard;
class IDatabase;
class PaymentProcessor;

class PayItineraryUseCase
{
    IDatabase &m_database;
    PaymentProcessor &m_paymentProcessor;

public:
    PayItineraryUseCase(IDatabase &database, PaymentProcessor &paymentProcessor);

    [[nodiscard]] std::vector<PaymentCard> getCustomerCards(const User &user);
    void addCard(const User &user, const PaymentCard &card);

    [[nodiscard]] PayItineraryResult execute(const User &user, const Itinerary &itinerary,
                                              const PaymentCard &card, int serviceChoice);
};
