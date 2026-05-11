#pragma once

#include "../model/user.hpp"
#include "frontend_interface.hpp"

class CreateItineraryUseCase;
class ListItinerariesUseCase;

class Application
{
    CreateItineraryUseCase &m_createItineraryUseCase;
    ListItinerariesUseCase &m_listItinerariesUseCase;

public:
    Application(CreateItineraryUseCase &createItineraryUseCase,
                ListItinerariesUseCase &listItinerariesUseCase);

    void createItinerary(User &, IFrontend &);
    void listItineraries(const User &, IFrontend &);
};
