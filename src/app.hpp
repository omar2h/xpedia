#pragma once

#include <memory>
#include <vector>

#include "domain/request_type.hpp"

class IFrontend;
class User;
class Itinerary;
class ItineraryItem;
class PaymentCard;
class ReservationRequest;
class ReservationRequestFactory;
class CreateItineraryUseCase;
class PayItineraryUseCase;
class ListItinerariesUseCase;

class App
{
    IFrontend &m_frontend;
    CreateItineraryUseCase &m_createItineraryUseCase;
    PayItineraryUseCase &m_payItineraryUseCase;
    ListItinerariesUseCase &m_listItinerariesUseCase;
    ReservationRequestFactory &m_requestFactory;

    void handleCreateItinerary(User &user);
    void addItemToItinerary(Itinerary &itinerary, RequestType type);
    bool handlePayment(User &user, const Itinerary &itinerary);

public:
    App(IFrontend &frontend,
        CreateItineraryUseCase &createItineraryUseCase,
        PayItineraryUseCase &payItineraryUseCase,
        ListItinerariesUseCase &listItinerariesUseCase,
        ReservationRequestFactory &requestFactory);
    void run();
};
