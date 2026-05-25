#include "create_itinerary_use_case.hpp"
#include "../services/reservation_service.hpp"
#include "../../domain/entities/itinerary.hpp"
#include "../../domain/entities/itinerary_item.hpp"
#include "../../domain/requests/reservation_request.hpp"
#include "../../domain/requests/flight_request.hpp"
#include "../../domain/requests/hotel_request.hpp"
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

std::vector<std::unique_ptr<ItineraryItem>> CreateItineraryUseCase::searchFlights(
    const FlightSearchInput &input)
{
    FlightRequest flightReq;
    flightReq.setFromCity(input.origin);
    flightReq.setToCity(input.destination);
    flightReq.setDate(input.departureDate);
    flightReq.setAdults(input.adults);
    return m_reservationService.getAvailableReservations(*request, RequestType::flight);
}

std::vector<std::unique_ptr<ItineraryItem>> CreateItineraryUseCase::searchHotels(
    const HotelSearchInput &input)
{
    auto request = m_requestFactory.getRequest(RequestType::hotel);
    auto *hotelReq = static_cast<HotelRequest *>(request.get());
    hotelReq->setCity(input.city);
    hotelReq->setFromDate(input.fromDate);
    hotelReq->setToDate(input.toDate);
    hotelReq->setAdults(input.adults);
    hotelReq->setChildren(input.children);
    hotelReq->setRooms(input.rooms);
    return m_reservationService.getAvailableReservations(*request, RequestType::hotel);
}

bool CreateItineraryUseCase::addFlightToItinerary(Itinerary &itinerary,
                                                  const FlightSearchInput &input,
                                                  const ItineraryItem &selectedItem)
{
    auto request = m_requestFactory.getRequest(RequestType::flight);
    auto *flightReq = static_cast<FlightRequest *>(request.get());
    flightReq->setFromCity(input.origin);
    flightReq->setToCity(input.destination);
    flightReq->setDate(input.departureDate);
    flightReq->setAdults(input.adults);

    auto reservation = m_reservationFactory.getReservation(RequestType::flight);
    if (!reservation)
        return false;
    reservation->setItem(selectedItem);
    reservation->applyRequest(*request);
    itinerary.addItem(std::move(reservation));
    return true;
}

bool CreateItineraryUseCase::addHotelToItinerary(Itinerary &itinerary,
                                                 const HotelSearchInput &input,
                                                 const ItineraryItem &selectedItem)
{
    auto request = m_requestFactory.getRequest(RequestType::hotel);
    auto *hotelReq = static_cast<HotelRequest *>(request.get());
    hotelReq->setCity(input.city);
    hotelReq->setFromDate(input.fromDate);
    hotelReq->setToDate(input.toDate);
    hotelReq->setAdults(input.adults);
    hotelReq->setChildren(input.children);
    hotelReq->setRooms(input.rooms);

    auto reservation = m_reservationFactory.getReservation(RequestType::hotel);
    if (!reservation)
        return false;
    reservation->setItem(selectedItem);
    reservation->applyRequest(*request);
    itinerary.addItem(std::move(reservation));
    return true;
}
