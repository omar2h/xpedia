#include "printer.hpp"
#include "menu_printer.hpp"
#include "../model/itinerary_item.hpp"

#include <iostream>
void Printer::printMenu(const std::vector<std::string> &strings)
{
    MenuPrinter::print(strings);
}

void Printer::printOptions(const std::vector<std::string> &options)
{
    int count{(int)options.size()};
    for (int i = 0; i < count; i++)
    {
        std::cout << i + 1 << ": " << options[i] << "\n";
    }
}
