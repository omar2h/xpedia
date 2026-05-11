#pragma once

#include <memory>
#include <functional>

class Customer;
class IFrontend;
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

    bool withdrawMoney(const PaymentCard &card, int service, const Itinerary &currItinerary);
    int makeReservations(Customer &customer, const Itinerary &currItinerary, IFrontend &frontend);
    int selectCard(Customer &customer, IFrontend &frontend);
    void addCard(Customer &customer, IFrontend &frontend);
};
