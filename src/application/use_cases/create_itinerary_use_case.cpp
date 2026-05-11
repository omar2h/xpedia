#include "create_itinerary_use_case.hpp"
#include "../services/reservation_service.hpp"
#include "../../domain/entities/itinerary.hpp"
#include "../../domain/entities/itinerary_item.hpp"
#include "../../application/requests/reservation_request.hpp"
#include "../../application/factories/reservation_request_factory.hpp"
#include "../../domain/factories/reservation_factory.hpp"
#include "../../domain/entities/flight_reservation.hpp"
#include "../../domain/entities/hotel_reservation.hpp"
#include "../../application/requests/flight_request.hpp"
#include "../../application/requests/hotel_request.hpp"
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

    if (type == RequestType::flight)
    {
        auto *flightReq = dynamic_cast<FlightRequest *>(request.get());
        auto *flightRes = dynamic_cast<FlightReservation *>(reservation.get());
        if (flightReq && flightRes)
        {
            flightRes->setFrom(flightReq->getFromCity());
            flightRes->setTo(flightReq->getToCity());
            flightRes->setAdults(flightReq->getAdults());
            flightRes->setChildren(flightReq->getChildren());
        }
    }
    else
    {
        auto *hotelReq = dynamic_cast<HotelRequest *>(request.get());
        auto *hotelRes = dynamic_cast<HotelReservation *>(reservation.get());
        if (hotelReq && hotelRes)
        {
            hotelRes->setCity(hotelReq->getCity());
            hotelRes->setRooms(hotelReq->getRooms());
            hotelRes->setAdults(hotelReq->getAdults());
            hotelRes->setChildren(hotelReq->getChildren());
        }
    }

    itinerary.addItem(std::move(reservation));
}
