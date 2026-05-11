#pragma once

#include <vector>
#include <memory>

class User;
class Itinerary;
class ItineraryItem;
class ReservationRequest;
class ReservationRequestFactory;
class ReservationFactory;
class ReservationService;
enum class RequestType;

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

    [[nodiscard]] std::vector<std::unique_ptr<ItineraryItem>> searchItems(
        RequestType type, ReservationRequest &request);

    void addItemToItinerary(Itinerary &itinerary, RequestType type,
                            std::unique_ptr<ReservationRequest> request,
                            const ItineraryItem &selectedItem);
};
