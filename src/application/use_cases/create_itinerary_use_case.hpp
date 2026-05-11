#pragma once

class User;
class IFrontend;
class ReservationRequestFactory;
class ReservationFactory;
class ReservationService;
class PayItineraryUseCase;
class Itinerary;
enum class RequestType;

class CreateItineraryUseCase
{
    ReservationRequestFactory &m_requestFactory;
    ReservationFactory &m_reservationFactory;
    ReservationService &m_reservationService;
    PayItineraryUseCase &m_payItineraryUseCase;

public:
    CreateItineraryUseCase(
        ReservationRequestFactory &requestFactory,
        ReservationFactory &reservationFactory,
        ReservationService &reservationService,
        PayItineraryUseCase &payItineraryUseCase);

    void execute(User &user, IFrontend &frontend);

private:
    void addNewItem(RequestType requestType, Itinerary &currItinerary, IFrontend &frontend);
};
