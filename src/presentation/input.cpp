#include "input.hpp"

#include "../exception.hpp"

#include <iostream>
#include <limits>

int ConsoleInput::readInt()
{
    int value{};
    std::cin >> value;

    if (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw ValidationException("Invalid input");
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return value;
}

double ConsoleInput::readDouble()
{
    double value{};
    std::cin >> value;

    if (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw ValidationException("Invalid input");
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return value;
}

std::string ConsoleInput::readLine()
{
    std::string input;
    std::getline(std::cin, input);
    return input;
}