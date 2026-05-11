#include "login_handler.hpp"
#include "../backend/backend.hpp"
#include <iostream>

LoginHandler::LoginHandler(Backend &backend) : m_backend(backend) {}

User LoginHandler::login()
{
    std::string email{};
    std::string password{};

    std::cout << "Enter Email: ";
    std::cin >> email;
    std::cout << "Enter Password: ";
    std::cin >> password;

    return m_backend.user_login(email, password);
}
