#include "email_validator.hpp"

bool EmailValidator::isValid(const std::string& email)
{
    return email.find('@') != std::string::npos && email.find('.') != std::string::npos &&
           email.find('@') < email.find('.');
}

std::string EmailValidator::getError(const std::string& email)
{
    if (email.empty())
        return "Email cannot be empty.";

    if (email.find('@') == std::string::npos)
        return "Email must contain '@'.";

    if (email.find('.') == std::string::npos)
        return "Email must contain a '.' after '@'.";

    if (email.find('@') > email.find('.'))
        return "'@' must appear before '.' in email.";

    return {};
}
