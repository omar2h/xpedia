#include "auth_presenter.hpp"
#include "../view/view_interface.hpp"
#include "../input.hpp"
#include "../presenter_helpers.hpp"
#include "../login_handler.hpp"
#include "../signup_handler.hpp"
#include "../../exception.hpp"

AuthPresenter::AuthPresenter(IView& view, IInput& input, LoginHandler& loginHandler, SignupHandler& signupHandler)
    : m_view(view), m_input(input), m_loginHandler(loginHandler), m_signupHandler(signupHandler) {}

AuthResult AuthPresenter::run()
{
    while (true)
    {
        m_view.showStartMenu();
        int choice = retryOnError(m_view, [&] { return m_input.readInt(1, 3); });

        switch (static_cast<StartMenuChoice>(choice))
        {
        case StartMenuChoice::Login:
            try
            {
                User user = m_loginHandler.login();
                m_view.displayWelcomeMessage(user.getFirstName(), user.getLastName());
                return {AppState::MainMenu, std::move(user)};
            }
            catch (const AppException& e)
            {
                m_view.showError(e.what());
            }
            break;
        case StartMenuChoice::SignUp:
            try
            {
                m_signupHandler.signup();
            }
            catch (const AppException& e)
            {
                m_view.showError(e.what());
            }
            break;
        case StartMenuChoice::Exit:
            return {AppState::Exit, std::nullopt};
        default:
            m_view.showError("Invalid choice");
            break;
        }
    }
}
