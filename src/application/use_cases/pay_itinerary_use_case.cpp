#include "pay_itinerary_use_case.hpp"
#include "../repositories/i_customer_repository.hpp"
#include "../repositories/i_itinerary_repository.hpp"
#include "../services/payment_service.hpp"
#include "../../domain/entities/itinerary.hpp"
#include "../../domain/entities/customer.hpp"
#include "../../domain/entities/user.hpp"
#include "../../domain/entities/payment_card.hpp"
#include <stdexcept>

PayItineraryUseCase::PayItineraryUseCase(ICustomerRepository &customerRepo,
                                         IItineraryRepository &itineraryRepo,
                                         PaymentProcessor &paymentProcessor)
    : m_customerRepo(customerRepo), m_itineraryRepo(itineraryRepo),
      m_paymentProcessor(paymentProcessor) {}

std::vector<PaymentCard> PayItineraryUseCase::getCustomerCards(const User &user)
{
    auto customer = m_customerRepo.findById(user.getId());
    if (!customer)
        return {};
    return customer->getCards();
}

void PayItineraryUseCase::addCard(const User &user, const PaymentCard &card)
{
    auto customer = m_customerRepo.findById(user.getId());
    if (!customer)
        throw std::runtime_error("Customer not found");
    customer->addCard(card);
    m_customerRepo.update(*customer);
}

PayItineraryResult PayItineraryUseCase::execute(const User &user, const Itinerary &itinerary,
                                                 const PaymentCard &card, int serviceChoice)
{
    if (itinerary.getReservations().empty())
        return {PayItineraryResult::NoReservations, "No Reservations to Pay"};

    auto customer = m_customerRepo.findById(user.getId());
    if (!customer)
        return {PayItineraryResult::Failed, "Customer not found"};

    int isConfirmed = m_paymentProcessor.makeReservations(*customer, card, serviceChoice, itinerary);

    if (isConfirmed == 1)
    {
        m_itineraryRepo.save(customer->getId(), itinerary);
        customer->addItineraryId(itinerary.getId());
        m_customerRepo.update(*customer);
        return {PayItineraryResult::Confirmed, "Reservation is Confirmed"};
    }

    return {PayItineraryResult::Failed, "Reservation Failed, Itinerary Cancelled"};
}
