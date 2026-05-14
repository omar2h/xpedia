#pragma once

#include <memory>
#include <vector>

#include "domain/request_type.hpp"

class IFrontend;
class User;
class Itinerary;
class ItineraryItem;
class PaymentCard;
class CreateItineraryUseCase;
class PayItineraryUseCase;
class ListItinerariesUseCase;

enum class StartMenuChoice { Login = 1, SignUp = 2, Exit = 3 };
enum class MainMenuChoice { ViewProfile = 1, CreateItinerary = 2, ListItineraries = 3, Logout = 4 };
enum class CreateItineraryMenuChoice { AddFlight = 1, AddHotel = 2, CheckOut = 3, Cancel = 4 };

class App
{
    IFrontend &m_frontend;
    CreateItineraryUseCase &m_createItineraryUseCase;
    PayItineraryUseCase &m_payItineraryUseCase;
    ListItinerariesUseCase &m_listItinerariesUseCase;

    void handleCreateItinerary(User &user);
    void addItemToItinerary(Itinerary &itinerary, RequestType type);
    bool handlePayment(User &user, const Itinerary &itinerary);

public:
    App(IFrontend &frontend,
        CreateItineraryUseCase &createItineraryUseCase,
        PayItineraryUseCase &payItineraryUseCase,
        ListItinerariesUseCase &listItinerariesUseCase);
    void run();
};
