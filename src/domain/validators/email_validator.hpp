#pragma once

#include <string>

class EmailValidator
{
  public:
    static bool isValid(const std::string& email);
    static std::string getError(const std::string& email);
};
