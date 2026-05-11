#include "payment_service.hpp"
#include "../database_interface.hpp"
#include "../payments/payment_strategy.hpp"
#include "../../model/payment_card.hpp"
#include "../../model/customer.hpp"
#include "../../model/itinerary.hpp"

PaymentProcessor::PaymentProcessor(
    IDatabase &database,
    std::function<std::unique_ptr<PaymentStrategy>(::PaymentService)> getPaymentService,
    std::function<bool(const Itinerary &)> confirmReservations)
    : m_database(database),
      m_getPaymentService(std::move(getPaymentService)),
      m_confirmReservations(std::move(confirmReservations)) {}

void PaymentProcessor::addCard(Customer &customer, const PaymentCard &card)
{
    customer.addCard(card);
    m_database.updateCustomerInfo(customer);
}

bool PaymentProcessor::withdrawMoney(
    const PaymentCard &card,
    int service,
    const Itinerary &currItinerary)
{
    auto paymentStrategy = m_getPaymentService(static_cast<PaymentService>(service - 1));
    bool isPaid = paymentStrategy->pay(card, currItinerary.totalCost());
    return isPaid;
}

int PaymentProcessor::makeReservations(Customer &customer, const PaymentCard &card, int serviceChoice, const Itinerary &currItinerary)
{
    bool isPaid = withdrawMoney(card, serviceChoice, currItinerary);
    if (!isPaid)
        return -1;
    return m_confirmReservations(currItinerary) ? 1 : 0;
}
