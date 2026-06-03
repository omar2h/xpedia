#pragma once

#include <functional>
#include <memory>

class Customer;
class PaymentCard;
class Itinerary;
class ICustomerRepository;
class PaymentStrategy;
enum class PaymentService;

class PaymentProcessor
{
    ICustomerRepository& m_customerRepo;
    std::function<std::unique_ptr<PaymentStrategy>(::PaymentService)> m_getPaymentService;
    std::function<bool(const Itinerary&)> m_confirmReservations;

  public:
    PaymentProcessor(ICustomerRepository& customerRepo,
                     std::function<std::unique_ptr<PaymentStrategy>(::PaymentService)> getPaymentService,
                     std::function<bool(const Itinerary&)> confirmReservations);

    [[nodiscard]] bool withdrawMoney(const Customer& customer, double amount, int service);
    [[nodiscard]] int makeReservations(Customer& customer, Itinerary& itinerary, int serviceChoice);
    void addCard(Customer& customer, const PaymentCard& card);
};
