#include "menuPrinter.h"
#include <iostream>
#include <cassert>

void MenuPrinter::print(const std::vector<std::string> &menu)
{
    assert(menu.size());
    int menuSize{(int)menu.size()};
    std::cout << "Menu:\n";
    for (int i = 0; i < menuSize; i++)
    {
        std::cout << "\t" << i + 1 << ": " << menu[i] << "\n";
    }
    std::cout << "\n";
    std::cout << "Your Choice: ";
}
