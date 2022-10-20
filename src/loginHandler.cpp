#include "loginHandler.h"
#include "backEnd.h"
#include <iostream>

User LoginHandler::login()
{
    std::string email{};
    std::string password{};

    std::cout << "Enter Email: ";
    std::cin >> email;
    std::cout << "Enter Password: ";
    std::cin >> password;

    return BackEnd::user_login(email, password);
}
