#include "pay_itinerary_use_case.hpp"
#include "../database_interface.hpp"
#include "../services/payment_service.hpp"
#include "../../domain/entities/itinerary.hpp"
#include "../../domain/entities/customer.hpp"
#include "../../domain/entities/user.hpp"
#include "../../domain/entities/payment_card.hpp"

PayItineraryUseCase::PayItineraryUseCase(IDatabase &database, PaymentProcessor &paymentProcessor)
    : m_database(database), m_paymentProcessor(paymentProcessor) {}

std::vector<PaymentCard> PayItineraryUseCase::getCustomerCards(const User &user)
{
    Customer customer = m_database.getCustomer(user);
    return customer.getCards();
}

void PayItineraryUseCase::addCard(const User &user, const PaymentCard &card)
{
    Customer customer = m_database.getCustomer(user);
    customer.addCard(card);
    m_database.updateCustomerInfo(customer);
}

PayItineraryResult PayItineraryUseCase::execute(const User &user, const Itinerary &itinerary,
                                                 const PaymentCard &card, int serviceChoice)
{
    if (itinerary.getReservations().empty())
        return {PayItineraryResult::NoReservations, "No Reservations to Pay"};

    Customer customer = m_database.getCustomer(user);

    int isConfirmed = m_paymentProcessor.makeReservations(customer, card, serviceChoice, itinerary);

    if (isConfirmed == 1)
    {
        m_database.saveItinerary(customer.getId(), itinerary);
        customer.addItineraryId(itinerary.getId());
        m_database.updateCustomerInfo(customer);
        return {PayItineraryResult::Confirmed, "Reservation is Confirmed"};
    }

    return {PayItineraryResult::Failed, "Reservation Failed, Itinerary Cancelled"};
}
