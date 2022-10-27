#include "error.h"
#include <iostream>

void Error::display_error(int errorCode)
{
    if (errorCode == 1)
    {
        std::cout << "\nInvalid Choice\n\n";
    }
    else if (errorCode == 2)
    {
        std::cout << "\nEmail/Phone already in use\n\n";
    }
    else if (errorCode == 3)
    {
        std::cout << "\nCan't open file\n\n";
    }
    else if (errorCode == 4)
        std::cout << "\nInvalid email/password(empty)\n\n";
    else if (errorCode == 5)
        std::cout << "\nInvalid email/password\n\n";
    else if (errorCode == 6)
        std::cout << "\nNo Reservations to Pay\n\n";
}
