#include "application.hpp"
#include "use_cases/create_itinerary_use_case.hpp"
#include "use_cases/list_itineraries_use_case.hpp"

Application::Application(CreateItineraryUseCase &createItineraryUseCase,
                         ListItinerariesUseCase &listItinerariesUseCase)
    : m_createItineraryUseCase(createItineraryUseCase),
      m_listItinerariesUseCase(listItinerariesUseCase) {}

void Application::createItinerary(User &user, IFrontend &frontend)
{
    m_createItineraryUseCase.execute(user, frontend);
}

void Application::listItineraries(const User &user, IFrontend &frontend)
{
    m_listItinerariesUseCase.execute(user, frontend);
}
