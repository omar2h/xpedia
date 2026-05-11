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

    return value;
}

int ConsoleInput::readInt(int low, int high)
{
    int choice{};
    std::cin >> choice;

    if (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw ValidationException("Invalid input");
    }

    if ((choice >= low && choice <= high) || choice == -1)
        return choice;

    throw ValidationException("Invalid Choice");
}

std::string ConsoleInput::readString()
{
    std::string input;
    std::cin >> input;
    return input;
}
