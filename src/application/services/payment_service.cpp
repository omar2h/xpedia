#include "payment_service.hpp"
#include "../repositories/i_customer_repository.hpp"
#include "../payments/payment_strategy.hpp"
#include "../../domain/entities/payment_card.hpp"
#include "../../domain/entities/customer.hpp"
#include "../../domain/entities/itinerary.hpp"

PaymentProcessor::PaymentProcessor(
    ICustomerRepository &customerRepo,
    std::function<std::unique_ptr<PaymentStrategy>(::PaymentService)> getPaymentService,
    std::function<bool(const Itinerary &)> confirmReservations)
    : m_customerRepo(customerRepo),
      m_getPaymentService(std::move(getPaymentService)),
      m_confirmReservations(std::move(confirmReservations)) {}

void PaymentProcessor::addCard(Customer &customer, const PaymentCard &card)
{
    customer.addCard(card);
    m_customerRepo.update(customer);
}

bool PaymentProcessor::withdrawMoney(
    const Customer &customer,
    double amount,
    int service)
{
    if (service < 1 || service > 3)
        return false;

    auto paymentStrategy = m_getPaymentService(static_cast<PaymentService>(service - 1));
    return paymentStrategy->pay(customer.getSelectedCard(), amount);
}

int PaymentProcessor::makeReservations(Customer &customer, Itinerary &itinerary, int serviceChoice)
{
    bool isPaid = withdrawMoney(customer, itinerary.totalCost(), serviceChoice);
    if (!isPaid)
        return -1;
    return m_confirmReservations(itinerary) ? 1 : 0;
}
