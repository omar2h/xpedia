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
}
