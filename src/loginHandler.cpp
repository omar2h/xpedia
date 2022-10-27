#include "loginHandler.h"
#include "backEnd.h"
#include "error.h"
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
        Error::display_error(e);
        login();
    }
}
