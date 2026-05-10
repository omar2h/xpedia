#include "login_handler.hpp"
#include "../backend/backend.hpp"
#include "../error.hpp"
#include <iostream>

User LoginHandler::login()
{
    std::string email{};
    std::string password{};

    std::cout << "Enter Email: ";
    std::cin >> email;
    std::cout << "Enter Password: ";
    std::cin >> password;

    return Backend::user_login(email, password);
}
