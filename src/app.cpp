#include "app.hpp"
#include "presentation/view/view_interface.hpp"
#include "presentation/input.hpp"
#include "presentation/presenters/auth_presenter.hpp"
#include "presentation/presenters/itinerary_presenter.hpp"
#include "presentation/presenter_helpers.hpp"
#include "presentation/mappers/user_profile_mapper.hpp"
#include "presentation/mappers/itinerary_mapper.hpp"
#include "domain/entities/user.hpp"
#include "application/use_cases/list_itineraries_use_case.hpp"
#include "application/results/list_itineraries_result.hpp"
#include "exception.hpp"
#include <optional>

App::App(IView &view, IInput &input,
         AuthPresenter &authPresenter,
         ItineraryPresenter &itineraryPresenter,
         ListItinerariesUseCase &listItinerariesUseCase)
    : m_view(view), m_input(input),
      m_authPresenter(authPresenter),
      m_itineraryPresenter(itineraryPresenter),
      m_listItinerariesUseCase(listItinerariesUseCase) {}

void App::run()
{
    AppState state = AppState::StartMenu;
    std::optional<User> currentUser;

    while (state != AppState::Exit)
    {
        switch (state)
        {
        case AppState::StartMenu:
        {
            auto result = m_authPresenter.run();
            state = result.state;
            if (result.user)
                currentUser = std::move(result.user);
            break;
        }
        case AppState::MainMenu:
            state = handleMainMenu(*currentUser);
            break;
        case AppState::Exit:
            break;
        }
    }
}

AppState App::handleMainMenu(User &user)
{
    m_view.showMainMenu();
    int choice;
    try
    {
        choice = readChoice(m_view, m_input, "", 1, 4);
    }
    catch (const AppException &e)
    {
        m_view.showError(e.what());
        return AppState::MainMenu;
    }

    switch (static_cast<MainMenuChoice>(choice))
    {
    case MainMenuChoice::CreateItinerary:
        m_itineraryPresenter.run(user);
        return AppState::MainMenu;
    case MainMenuChoice::ViewItineraries:
    {
        auto result = m_listItinerariesUseCase.execute(user);
        if (result.success)
        {
            std::vector<ItineraryViewModel> viewModels;
            for (const auto &it : result.itineraries)
                viewModels.push_back(toItineraryViewModel(it));
            m_view.displayItineraries(viewModels);
        }
        else
            m_view.showMessage(result.message);
        return AppState::MainMenu;
    }
    case MainMenuChoice::ViewProfile:
        m_view.displayUserProfile(toUserProfileViewModel(user));
        return AppState::MainMenu;
    case MainMenuChoice::Logout:
        return AppState::StartMenu;
    default:
        m_view.showError("Invalid choice");
        return AppState::MainMenu;
    }
}
