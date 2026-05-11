#include "error.hpp"
#include <iostream>

void Error::display(ErrorCode code)
{
    switch (code)
    {
    case ErrorCode::invalid_choice:
        std::cout << "\nInvalid Choice\n\n";
        break;
    case ErrorCode::email_phone_in_use:
        std::cout << "\nEmail/Phone already in use\n\n";
        break;
    case ErrorCode::cant_open_file:
        std::cout << "\nCan't open file\n\n";
        break;
    case ErrorCode::invalid_email_password_empty:
        std::cout << "\nInvalid email/password(empty)\n\n";
        break;
    case ErrorCode::invalid_email_password:
        std::cout << "\nInvalid email/password\n\n";
        break;
    case ErrorCode::no_reservations_to_pay:
        std::cout << "\nNo Reservations to Pay\n\n";
        break;
    }
}
