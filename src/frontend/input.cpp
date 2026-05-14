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
    return readInt(low, high, false);
}

int ConsoleInput::readInt(int low, int high, bool allowCancel)
{
    int choice = readInt();

    if (choice >= low && choice <= high)
        return choice;

    if (allowCancel && choice == -1)
        return -1;

    throw ValidationException("Invalid Choice");
}

std::string ConsoleInput::readString()
{
    std::string input;
    // Discard any leftover characters from previous extraction (e.g., after >>)
    if (std::cin.rdbuf()->in_avail() > 0)
    {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::getline(std::cin, input);
    return input;
}
