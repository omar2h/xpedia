#pragma once

#include <vector>
#include <memory>

#include "../../domain/request_type.hpp"

class User;
class Itinerary;
class ItineraryItem;
class ReservationRequest;
class ReservationRequestFactory;
class ReservationFactory;
class ReservationService;

class CreateItineraryUseCase
{
    ReservationRequestFactory &m_requestFactory;
    ReservationFactory &m_reservationFactory;
    ReservationService &m_reservationService;

public:
    CreateItineraryUseCase(
        ReservationRequestFactory &requestFactory,
        ReservationFactory &reservationFactory,
        ReservationService &reservationService);

    [[nodiscard]] Itinerary createItinerary();

    [[nodiscard]] std::unique_ptr<ReservationRequest> makeRequest(RequestType type);

    [[nodiscard]] std::vector<std::unique_ptr<ItineraryItem>> searchItems(
        RequestType type, ReservationRequest &request);

    [[nodiscard]] bool addItemToItinerary(Itinerary &itinerary, RequestType type,
                                          std::unique_ptr<ReservationRequest> request,
                                          const ItineraryItem &selectedItem);
};
