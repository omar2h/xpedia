#pragma once

#include <memory>
#include <functional>

class Customer;
class PaymentCard;
class Itinerary;
class IDatabase;
class PaymentStrategy;
enum class PaymentService;

class PaymentProcessor
{
    IDatabase &m_database;
    std::function<std::unique_ptr<PaymentStrategy>(::PaymentService)> m_getPaymentService;
    std::function<bool(const Itinerary &)> m_confirmReservations;

public:
    PaymentProcessor(
        IDatabase &database,
        std::function<std::unique_ptr<PaymentStrategy>(::PaymentService)> getPaymentService,
        std::function<bool(const Itinerary &)> confirmReservations);

    [[nodiscard]] bool withdrawMoney(const PaymentCard &card, int service, const Itinerary &currItinerary);
    [[nodiscard]] int makeReservations(Customer &customer, const PaymentCard &card, int serviceChoice, const Itinerary &currItinerary);
    void addCard(Customer &customer, const PaymentCard &card);
};
