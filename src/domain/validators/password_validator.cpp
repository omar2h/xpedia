#include "password_validator.hpp"
#include <cctype>

bool PasswordValidator::isValid(const std::string &password)
{
    if (password.size() < 8)
        return false;

    bool hasDigit = false;
    bool hasUpper = false;
    bool hasLower = false;

    for (char c : password)
    {
        if (std::isdigit(static_cast<unsigned char>(c)))
            hasDigit = true;
        if (std::isupper(static_cast<unsigned char>(c)))
            hasUpper = true;
        if (std::islower(static_cast<unsigned char>(c)))
            hasLower = true;
    }

    return hasDigit && hasUpper && hasLower;
}

std::string PasswordValidator::getError(const std::string &password)
{
    if (password.size() < 8)
        return "Password must be at least 8 characters.";

    bool hasDigit = false;
    bool hasUpper = false;
    bool hasLower = false;

    for (char c : password)
    {
        if (std::isdigit(static_cast<unsigned char>(c)))
            hasDigit = true;
        if (std::isupper(static_cast<unsigned char>(c)))
            hasUpper = true;
        if (std::islower(static_cast<unsigned char>(c)))
            hasLower = true;
    }

    if (!hasDigit || !hasUpper || !hasLower)
        return "Password must contain at least one digit, one uppercase letter, and one lowercase letter.";

    return {};
}
