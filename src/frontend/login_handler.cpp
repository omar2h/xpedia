#include "login_handler.hpp"
#include "output.hpp"
#include "input.hpp"
#include "../application/application.hpp"

LoginHandler::LoginHandler(Application &backend, IOutput &output, IInput &input)
    : m_application(backend), m_output(output), m_input(input) {}

User LoginHandler::login()
{
    m_output.write("Enter Email: ");
    std::string email = m_input.readString();
    m_output.write("Enter Password: ");
    std::string password = m_input.readString();

    return m_application.userLogin(email, password);
}
