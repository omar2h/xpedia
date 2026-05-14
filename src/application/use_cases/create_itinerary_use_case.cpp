#include "create_itinerary_use_case.hpp"
#include "../services/reservation_service.hpp"
#include "../../domain/entities/itinerary.hpp"
#include "../../domain/entities/itinerary_item.hpp"
#include "../../application/requests/reservation_request.hpp"
#include "../../application/factories/reservation_request_factory.hpp"
#include "../../domain/factories/reservation_factory.hpp"
#include "../../util/id_generator.hpp"
#include <memory>
#include <vector>

CreateItineraryUseCase::CreateItineraryUseCase(
    ReservationRequestFactory &requestFactory,
    ReservationFactory &reservationFactory,
    ReservationService &reservationService)
    : m_requestFactory(requestFactory),
      m_reservationFactory(reservationFactory),
      m_reservationService(reservationService) {}

Itinerary CreateItineraryUseCase::createItinerary()
{
    Itinerary itinerary;
    itinerary.setId(generateId());
    return itinerary;
}

std::vector<std::unique_ptr<ItineraryItem>> CreateItineraryUseCase::searchItems(
    RequestType type, ReservationRequest &request)
{
    return m_reservationService.getAvailableReservations(&request, type);
}

void CreateItineraryUseCase::addItemToItinerary(Itinerary &itinerary, RequestType type,
                                                std::unique_ptr<ReservationRequest> request,
                                                const ItineraryItem &selectedItem)
{
    auto reservation = m_reservationFactory.getReservation(type);
    reservation->setItem(selectedItem);
    reservation->applyRequest(*request);
    itinerary.addItem(std::move(reservation));
}
