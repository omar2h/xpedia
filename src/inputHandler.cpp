#include "inputHandler.h"
#include <iostream>

int InputHandler::get_choice(int low, int high)
{
    int choice{};
    std::cin >> choice;
    if (choice >= low && choice <= high)
        return choice;
    else
        throw 1;
}
