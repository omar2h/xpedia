#include "signup_handler.hpp"
#include "output.hpp"
#include "input.hpp"
#include "../model/user.hpp"
#include "../application/application.hpp"

SignupHandler::SignupHandler(Application &backend, IOutput &output, IInput &input)
    : m_application(backend), m_output(output), m_input(input) {}

void SignupHandler::signup()
{
    m_output.write("First Name: ");
    std::string firstName = m_input.readString();
    m_output.write("Last Name: ");
    std::string lastName = m_input.readString();
    m_output.write("Email: ");
    std::string email = m_input.readString();
    m_output.write("Phone: ");
    std::string phone = m_input.readString();
    m_output.write("Password: ");
    std::string password = m_input.readString();

    User usr(firstName, lastName, email, phone, password);

    m_application.saveUserInDb(usr);
}
