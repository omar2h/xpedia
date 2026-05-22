// auth_presenter.cpp

#include "auth_presenter.hpp"

#include "../view/view_interface.hpp"
#include "../input.hpp"
#include "../presenter_helpers.hpp"

#include "../../application/services/auth_service.hpp"

#include "../../domain/entities/user.hpp"

#include "../../domain/validators/email_validator.hpp"
#include "../../domain/validators/password_validator.hpp"

#include "../../exception.hpp"

AuthPresenter::AuthPresenter(IView &view, IInput &input, AuthService &authService)
    : m_view(view), m_input(input), m_authService(authService) {}

AuthResult AuthPresenter::run()
{
    while (true)
    {
        m_view.showStartMenu();
        int choice = retryOnError(m_view, [&]
                                  { return m_input.readInt(); });

        if (choice < 1 || choice > 3)
        {
            m_view.showError("Invalid choice");
            continue;
        }

        switch (static_cast<StartMenuChoice>(choice))
        {
        case StartMenuChoice::Login:
            try
            {
                User user = login();
                m_view.displayWelcomeMessage(user.getFirstName(), user.getLastName());
                return {AppState::MainMenu, std::move(user)};
            }
            catch (const AppException &e)
            {
                m_view.showError(e.what());
            }

            break;

        case StartMenuChoice::SignUp:
            try
            {
                signup();
                m_view.showMessage("Account created successfully");
            }
            catch (const AppException &e)
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

User AuthPresenter::login()
{
    m_view.showPrompt("Enter Email: ");
    std::string email = m_input.readLine();

    m_view.showPrompt("Enter Password: ");
    std::string password = m_input.readLine();

    return m_authService.login(email, password);
}

void AuthPresenter::signup()
{
    m_view.showPrompt("First Name: ");
    std::string firstName = m_input.readLine();

    m_view.showPrompt("Last Name: ");
    std::string lastName = m_input.readLine();

    std::string email;

    while (true)
    {
        m_view.showPrompt("Email: ");
        email = m_input.readLine();

        if (EmailValidator::isValid(email))
            break;

        m_view.showError(EmailValidator::getError(email));
    }

    m_view.showPrompt("Phone: ");
    std::string phone = m_input.readLine();
    std::string password;

    while (true)
    {
        m_view.showPrompt("Password: ");
        password = m_input.readLine();

        if (PasswordValidator::isValid(password))
            break;

        m_view.showError(PasswordValidator::getError(password));
    }

    User user(firstName, lastName, email, phone, password);
    m_authService.signup(user);
}