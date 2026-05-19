#include "signup_handler.hpp"
#include "output.hpp"
#include "input.hpp"
#include "../domain/entities/user.hpp"
#include "../domain/validators/email_validator.hpp"
#include "../domain/validators/password_validator.hpp"
#include "../application/services/auth_service.hpp"

SignupHandler::SignupHandler(AuthService &authService, IOutput &output, IInput &input)
    : m_authService(authService), m_output(output), m_input(input) {}

void SignupHandler::signup()
{
    m_output.write("First Name: ");
    std::string firstName = m_input.readString();
    m_output.write("Last Name: ");
    std::string lastName = m_input.readString();
    std::string email;
    while (true)
    {
        m_output.write("Email: ");
        email = m_input.readString();

        if (EmailValidator::isValid(email))
            break;

        m_output.writeLine(EmailValidator::getError(email));
    }

    m_output.write("Phone: ");
    std::string phone = m_input.readString();

    std::string password;
    while (true)
    {
        m_output.write("Password: ");
        password = m_input.readString();

        if (PasswordValidator::isValid(password))
            break;

        m_output.writeLine(PasswordValidator::getError(password));
    }

    User usr(firstName, lastName, email, phone, password);

    m_authService.signup(usr);
}
