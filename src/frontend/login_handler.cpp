#include "login_handler.hpp"
#include "output.hpp"
#include "input.hpp"
#include "../application/services/auth_service.hpp"

LoginHandler::LoginHandler(AuthService &authService, IOutput &output, IInput &input)
    : m_authService(authService), m_output(output), m_input(input) {}

User LoginHandler::login()
{
    m_output.write("Enter Email: ");
    std::string email = m_input.readString();
    m_output.write("Enter Password: ");
    std::string password = m_input.readString();

    return m_authService.login(email, password);
}
