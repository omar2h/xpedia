#pragma once

#include <string>

class PasswordValidator
{
public:
    static bool isValid(const std::string &password);
    static std::string getError(const std::string &password);
};
