#include "pay_itinerary_use_case.hpp"
#include "../../domain/entities/customer.hpp"
#include "../../domain/entities/itinerary.hpp"
#include "../../domain/entities/payment_card.hpp"
#include "../../domain/entities/user.hpp"
#include "../repositories/i_customer_repository.hpp"
#include "../repositories/i_itinerary_repository.hpp"
#include "../services/payment_service.hpp"
#include <stdexcept>

PayItineraryUseCase::PayItineraryUseCase(ICustomerRepository& customerRepo, IItineraryRepository& itineraryRepo,
                                         PaymentProcessor& paymentProcessor)
    : m_customerRepo(customerRepo), m_itineraryRepo(itineraryRepo), m_paymentProcessor(paymentProcessor)
{
}

std::vector<PaymentCard> PayItineraryUseCase::getCustomerCards(const User& user)
{
    auto customer = m_customerRepo.findById(user.getId());
    if (!customer)
        return {};
    return customer->getCards();
}

void PayItineraryUseCase::addCard(const User& user, const PaymentCard& card)
{
    auto customer = m_customerRepo.findById(user.getId());
    if (!customer)
        throw std::runtime_error("Customer not found");
    customer->addCard(card);
    m_customerRepo.update(*customer);
}

Result<Itinerary> PayItineraryUseCase::execute(Customer& customer, Itinerary& itinerary, int serviceChoice)
{
    int isConfirmed = m_paymentProcessor.makeReservations(customer, itinerary, serviceChoice);

    if (isConfirmed == 1)
    {
        m_itineraryRepo.save(customer.getId(), itinerary);
        customer.addItineraryId(itinerary.getId());
        m_customerRepo.update(customer);
        return Result<Itinerary>::success(itinerary);
    }

    if (isConfirmed == -1)
    {
        return Result<Itinerary>::failure("Payment failed. Itinerary was not saved.");
    }

    return Result<Itinerary>::failure("Reservation confirmation failed. Itinerary was not saved.");
}
