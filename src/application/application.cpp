#include "application.hpp"
#include "../exception.hpp"
#include "database_interface.hpp"
#include "frontend_interface.hpp"
#include "../model/factories/reservation_request_factory.hpp"
#include "../model/factories/reservation_factory.hpp"
#include "../util/id_generator.hpp"

Application::Application(IDatabase &database,
                         ReservationService &reservationService,
                         PaymentProcessor &paymentService,
                         ReservationRequestFactory &requestFactory,
                         ReservationFactory &reservationFactory)
    : m_database(database),
      m_reservationService(reservationService),
      m_paymentService(paymentService),
      m_requestFactory(requestFactory),
      m_reservationFactory(reservationFactory) {}

void Application::addCard(Customer &customer, IFrontend &frontend)
{
    PaymentCard card = frontend.readCard();
    customer.addCard(card);

    m_database.updateCustomerInfo(customer);
}

void Application::payItinerary(const Itinerary &currItinerary, const User &user, IFrontend &frontend)
{
    if (currItinerary.getReservations().empty())
        throw BusinessException("No Reservations to Pay");

    Customer customer = m_database.getCustomer(user);

    int isConfirmed = m_paymentService.makeReservations(customer, currItinerary, frontend);

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

void Application::addNewItem(RequestType requestType, Itinerary &currItinerary, IFrontend &frontend)
{
    auto request = m_requestFactory.getRequest(requestType);

    frontend.readRequestData(*request, requestType);

    std::vector<std::unique_ptr<ItineraryItem>> items = m_reservationService.getAvailableReservations(request.get(), requestType);

    int choice = frontend.readReservationChoice(items);

    if (choice == -1)
        return;

    auto reservation = m_reservationFactory.getReservation(requestType);

    reservation->setItem(*items[choice - 1]);
    reservation->setRequest(std::move(request));

    currItinerary.addItem(std::move(reservation));
}

void Application::listItineraries(const User &user, IFrontend &frontend)
{
    bool isCustomer = m_database.checkUserIsCustomer(user);

    if (!isCustomer)
    {
        frontend.showMessage("User has no itineraries");
        return;
    }

    Customer customer = m_database.getCustomer(user);

    if (customer.getItinerariesIds().empty())
    {
        frontend.showMessage("User has no itineraries");
        return;
    }

    std::vector<Itinerary> customerItineraries = m_database.getCustomerItineraries(customer.getId());

    frontend.displayItineraries(customerItineraries);
}

void Application::createItinerary(User &user, IFrontend &frontend)
{
    Itinerary currItinerary;

    while (true)
    {
        currItinerary.setId(generateId());

        int choice = frontend.displayCreateItineraryMenu();

        if (choice == 1)
        {
            addNewItem(RequestType::flight, currItinerary, frontend);
        }
        else if (choice == 2)
        {
            addNewItem(RequestType::hotel, currItinerary, frontend);
        }
        else if (choice == 3)
        {
            frontend.displayItinerary(currItinerary);

            payItinerary(currItinerary, user, frontend);

            currItinerary.clear();
            return;
        }
        else if (choice == 4)
        {
            currItinerary.clear();
            return;
        }
    }
}
