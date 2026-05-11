#include "signup_handler.hpp"
#include "../model/user.hpp"
#include "../application/application.hpp"
#include <string>
#include <iostream>

SignupHandler::SignupHandler(Application &backend) : m_application(backend) {}

void SignupHandler::signup()
{
    std::string firstName{};
    std::string lastName{};
    std::string email{};
    std::string phone{};
    std::string id{};
    std::string password{};

    std::cout << "First Name: ";
    std::cin >> firstName;
    std::cout << "Last Name: ";
    std::cin >> lastName;
    std::cout << "Email: ";
    std::cin >> email;
    std::cout << "Phone: ";
    std::cin >> phone;
    std::cout << "Password: ";
    std::cin >> password;

    User usr(firstName, lastName, email, phone, password);

    m_application.saveUserInDb(usr);
}
