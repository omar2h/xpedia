#include "loginHandler.h"
#include "../backend/backEnd.h"
#include "../error.h"
#include <iostream>

User LoginHandler::login()
{
    std::string email{};
    std::string password{};

    std::cout << "Enter Email: ";
    std::cin >> email;
    std::cout << "Enter Password: ";
    std::cin >> password;

    try
    {
        return BackEnd::user_login(email, password);
    }
    catch (int e)
    {
        throw e;
    }
}
