#include "payment_service.hpp"
#include "../database_interface.hpp"
#include "../payments/payment_strategy.hpp"
#include "../frontend_interface.hpp"
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

void PaymentProcessor::addCard(Customer &customer, IFrontend &frontend)
{
    PaymentCard card = frontend.readCard();
    customer.addCard(card);

    m_database.updateCustomerInfo(customer);
}

int PaymentProcessor::selectCard(Customer &customer, IFrontend &frontend)
{
    int choice{};

    while (true)
    {
        choice =
            frontend.displayPaymentOptions(customer.getCards());

        if (choice == -1)
            return -1;

        if (choice == 0)
            addCard(customer, frontend);
        else
            break;
    }

    return choice;
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

int PaymentProcessor::makeReservations(Customer &customer, const Itinerary &currItinerary, IFrontend &frontend)
{
    int choice = selectCard(customer, frontend);

    if (choice == -1)
        return -1;

    PaymentCard card = customer.getCards()[choice - 1];

    choice = frontend.displayPaymentServices();

    if (choice == -1)
        return choice;

    bool isPaid = withdrawMoney(card, choice, currItinerary);

    if (isPaid)
        frontend.showMessage("Transaction Succeeded");
    else
    {
        frontend.showError("Transaction Failed");
        return -1;
    }

    return m_confirmReservations(currItinerary) ? 1 : 0;
}
