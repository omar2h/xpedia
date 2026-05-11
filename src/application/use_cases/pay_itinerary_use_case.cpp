#include "pay_itinerary_use_case.hpp"
#include "../database_interface.hpp"
#include "../frontend_interface.hpp"
#include "../services/payment_service.hpp"
#include "../../model/itinerary.hpp"
#include "../../model/customer.hpp"
#include "../../model/user.hpp"
#include "../../exception.hpp"

PayItineraryUseCase::PayItineraryUseCase(IDatabase &database, PaymentProcessor &paymentProcessor)
    : m_database(database), m_paymentProcessor(paymentProcessor) {}

void PayItineraryUseCase::execute(const Itinerary &currItinerary, const User &user, IFrontend &frontend)
{
    if (currItinerary.getReservations().empty())
        throw BusinessException("No Reservations to Pay");

    Customer customer = m_database.getCustomer(user);

    int isConfirmed = m_paymentProcessor.makeReservations(customer, currItinerary, frontend);

    if (isConfirmed == 1)
    {
        frontend.showMessage("Reservation is Confirmed");

        m_database.saveItinerary(customer.getId(), currItinerary);

        customer.addItineraryId(currItinerary.getId());

        m_database.updateCustomerInfo(customer);

        return;
    }

    if (isConfirmed == 0)
        frontend.showError("Reservation Failed, Itinerary Cancelled");
}
