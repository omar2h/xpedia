#include "error.hpp"
#include <iostream>

void Error::display(ErrorCode code)
{
    switch (code)
    {
    case ErrorCode::invalidChoice:
        std::cout << "\nInvalid Choice\n\n";
        break;
    case ErrorCode::emailPhoneInUse:
        std::cout << "\nEmail/Phone already in use\n\n";
        break;
    case ErrorCode::cantOpenFile:
        std::cout << "\nCan't open file\n\n";
        break;
    case ErrorCode::invalidEmailPasswordEmpty:
        std::cout << "\nInvalid email/password(empty)\n\n";
        break;
    case ErrorCode::invalidEmailPassword:
        std::cout << "\nInvalid email/password\n\n";
        break;
    case ErrorCode::noReservationsToPay:
        std::cout << "\nNo Reservations to Pay\n\n";
        break;
    }
}
