#include "signupHandler.h"
#include "../model/user.h"
#include "../backend/backEnd.h"
#include "../error.h"
#include <string>
#include <iostream>

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
    try
    {
        BackEnd::save_user_in_db(usr);
        return;
    }
    catch (int e)
    {
        Error::display_error(e);
        signup();
    }
}