#include "create_itinerary_use_case.hpp"
#include "pay_itinerary_use_case.hpp"
#include "../frontend_interface.hpp"
#include "../services/reservation_service.hpp"
#include "../../model/factories/reservation_request_factory.hpp"
#include "../../model/factories/reservation_factory.hpp"
#include "../../model/itinerary.hpp"
#include "../../model/requests/reservation_request.hpp"
#include "../../util/id_generator.hpp"
#include <memory>
#include <vector>

CreateItineraryUseCase::CreateItineraryUseCase(
    ReservationRequestFactory &requestFactory,
    ReservationFactory &reservationFactory,
    ReservationService &reservationService,
    PayItineraryUseCase &payItineraryUseCase)
    : m_requestFactory(requestFactory),
      m_reservationFactory(reservationFactory),
      m_reservationService(reservationService),
      m_payItineraryUseCase(payItineraryUseCase) {}

void CreateItineraryUseCase::addNewItem(RequestType requestType, Itinerary &currItinerary, IFrontend &frontend)
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

void CreateItineraryUseCase::execute(User &user, IFrontend &frontend)
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

            m_payItineraryUseCase.execute(currItinerary, user, frontend);

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
