#include "input_handler.hpp"
#include <iostream>

int InputHandler::get_choice(int low, int high)
{
    int choice{};
    std::cin >> choice;
    if ((choice >= low && choice <= high) || choice == -1)
        return choice;
    else
        throw 1;
}
